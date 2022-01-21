import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Set;

public class orderbook 
{
    private Map<String, List<order>> m_buyOrderbook = new HashMap<String, List<order>>();
    private Map<String, List<order>> m_sellOrderbook = new HashMap<String, List<order>>();

    // Getting the crypto name when initialising the constructor
    public orderbook(Set<String> cryptosAvailable)
    {
        for (String crypto : cryptosAvailable)
        {
            List<order> buyLimitOrders = new ArrayList<order>();
            List<order> sellLimitOrders = new ArrayList<order>();

            // Key = crypto, Value = Buy/Sell orders for it
            m_buyOrderbook.put(crypto, buyLimitOrders);
            m_sellOrderbook.put(crypto, sellLimitOrders);
        }
    }

    public List<order> getBuyOrders(String cryptoName)
    {
        return m_buyOrderbook.get(cryptoName);
    }

    public List<order> getSellOrders(String cryptoName)
    {
        return m_sellOrderbook.get(cryptoName);
    }

    public void addBuyOrder(order orderToAdd)
    {
        String cryptoName = orderToAdd.getCryptoName();
        List<order> newCryptoBuyOrder = getBuyOrders(cryptoName);

        newCryptoBuyOrder.add(orderToAdd);
        // Sort order list

        m_buyOrderbook.replace(cryptoName, newCryptoBuyOrder);
    }

    public void addSellOrder(order orderToAdd)
    {
        String cryptoName = orderToAdd.getCryptoName();
        List<order> newCryptoBuyOrder = getSellOrders(cryptoName);

        newCryptoBuyOrder.add(orderToAdd);

        m_buyOrderbook.replace(cryptoName, newCryptoBuyOrder);
    }
}
