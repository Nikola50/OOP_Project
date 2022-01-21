import java.util.List;

public class matchingEngine 
{
    private orderbook m_orderbook = null;

    public matchingEngine(orderbook orderbook)
    {
        m_orderbook = orderbook;
    }

    public void processOrder(order orderToProcess)
    {
        List<order> orderList = null;
        crypto cryptoToExchange = orderToProcess.getCrypto();

        // Get the list to match the order
        orderList = getMatchingList(orderToProcess, cryptoToExchange.getName());
        if (!orderToProcess.isLimitOrder() && (orderList == null || orderList.isEmpty()))
        {
            // No matching orders present
            return;
        }
        else if (orderToProcess.isLimitOrder() && (orderList == null || orderList.isEmpty()))
        {
            if (orderToProcess.isSellOrder())
            {
                m_orderbook.addSellOrder(orderToProcess);
            }
            else if (orderToProcess.isBuyOrder())
            {
                m_orderbook.addBuyOrder(orderToProcess);
            }

            return;
        }

        float amountToFill = orderToProcess.getCryptoQuantity();

        /////////// GO THROUGH ORDERS OF THE OPPOSITE LIST ///////////// 
        
        int ordersFilled = 0;
        for (order individualOrder : orderList)
        {
            ordersFilled++;
            float matchingAmount = individualOrder.getCryptoQuantity();

            //////////// FILL THE ORIGINAL ORDER //////////////

            if (orderToProcess.isSellOrder())
            {
                // Validate bid price
                if (orderToProcess.isLimitOrder() && !validateBidAndAskPrice(orderToProcess, individualOrder))
                {
                    continue;
                }

                if (amountToFill == matchingAmount)
                {
                    // Fill the market order with necessary details
                    user buyerUser = individualOrder.getDestination();
                    fiat buyerCurrency = individualOrder.getDestinationCurrency();
                    orderToProcess.addDestinationDetails(buyerUser, buyerCurrency);
                }

            }
            else if (orderToProcess.isBuyOrder())    
            {
                // Validate ask price
                if (orderToProcess.isLimitOrder() && !validateBidAndAskPrice(individualOrder, orderToProcess))
                {
                    continue;
                }
                
                if (amountToFill == matchingAmount)
                {
                    
                    // Fill the market order with necessary details
                    user sellerUser = individualOrder.getSource();
                    fiat sellerCurrency = individualOrder.getSourceCurrency();
                    orderToProcess.addSourceDetails(sellerUser, sellerCurrency);
                }
            }

            // orderToProcess.getOrderDetails();
            // Once the original order is complete it is executed
            orderToProcess.executeTransaction();


            // amountToFill -= matchingAmount;
        }

        // Remove orders if more orders than one are executed
        for (int i = 0; i < ordersFilled; i++)
        {
            // Remove the first order for each iteration
            orderList.remove(0);
        }
    }

    private List<order> getMatchingList(order order, String crypto)
    {
        if (order.isSellOrder())
        {
            return m_orderbook.getBuyOrders(crypto);
        }
        else if (order.isBuyOrder())
        {
            return m_orderbook.getSellOrders(crypto);
        }

        return null;
    }

    private boolean validateBidAndAskPrice(order sellOrder, order buyOrder)
    {
        if (sellOrder.getDestinationCurrency() != null && buyOrder.getSourceCurrency() != null)
        {
            float sellPrice = sellOrder.getDestinationCurrency().getFinalValue();
            float buyPrice = buyOrder.getSourceCurrency().getFinalValue();

            if (sellPrice > buyPrice)
            {
                // Return false if the buy price is too low
                return false;
            }
        }
        else
        {
            return false;
        }

        return true;
    }
}
