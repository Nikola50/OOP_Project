import java.util.Map;

public class order 
{
    protected user m_orderSource = null;
    protected user m_orderDestination = null;
    protected crypto m_cryptoExchanged = null;
    protected fiat m_currencySource = null;
    protected fiat m_currencyDestination = null;
    protected boolean m_limitedOrder = false;
    protected boolean m_orderFilled = false;

    public order(user source, user destination, fiat sourceCurrency, fiat destinationCurrency, crypto cryptoExchanged)
    {
        m_orderSource = source;
        m_currencySource = sourceCurrency;
        m_orderDestination = destination;
        m_currencyDestination = destinationCurrency;
        m_cryptoExchanged = cryptoExchanged;
    }

    public void getOrderDetails()
    {
        System.out.println("m_orderSource: " + m_orderSource + "\n" +
                           "m_currencySource: " + m_currencySource + "\n" +
                           "m_orderDestination: " + m_orderDestination + "\n" + 
                           "m_currencyDestination: " + m_currencyDestination + "\n" +
                           "m_cryptoExchanged" + m_cryptoExchanged + "\n");
    }

    // SOURCE DETAILS HANDLING

    public void addSourceDetails(user source, fiat sourceCurrency)
    {
        m_orderSource = source;
        m_currencySource = sourceCurrency;
    }

    public user getSource()
    {
        return m_orderSource;
    }

    public fiat getSourceCurrency()
    {
        return m_currencySource;
    }

    // DESTINATION DETAILS HANDLING

    public void addDestinationDetails(user destination, fiat destinationCurrency)
    {
        m_orderDestination = destination;
        m_currencyDestination = destinationCurrency;
    }

    public user getDestination()
    {
        return m_orderDestination;
    }

    public fiat getDestinationCurrency()
    {
        return m_currencyDestination;
    }

    public boolean isOrderEmpty()
    {
        return m_orderSource == null && m_orderDestination == null;
    }

    public boolean isSellOrder()
    {
        // If the Source is known and the destination is not, then it is a sell order
        return m_orderSource != null && m_orderDestination == null;
    }

    public boolean isBuyOrder()
    {
        // If the Source is not known and the destination is, then it is a buy order
        return m_orderSource == null && m_orderDestination != null;
    }

    public boolean isLimitOrder()
    {
        return m_limitedOrder;
    }

    public crypto getCrypto()
    {
        return m_cryptoExchanged;
    }

    public String getCryptoName()
    {
        return m_cryptoExchanged.getName();
    }

    public int getCryptoQuantity()
    {
        return m_cryptoExchanged.getQuantity();
    }

    public void fillOrder()
    {
        m_orderFilled = true;
    }

    public void executeTransaction()
    {
        /////// Source wallet transfer ////////////

        Map<String, Float> sourceWallet = m_orderSource.getWallet();

        // Reducing the money in the wallet for the currency
        float fiatAmount = 0f;
        if (sourceWallet.containsKey(m_currencyDestination.getName()))
        {
            fiatAmount = sourceWallet.get(m_currencyDestination.getName());
            
        }
        
        float fiatTransfer = m_currencyDestination.getFinalValue();
        float newFiatAmount = fiatAmount + fiatTransfer;
        

        // Adding crypto to the same wallet
        float cryptoAmount = 0f;
        if (sourceWallet.containsKey(m_cryptoExchanged.getName()))
        {
            cryptoAmount = sourceWallet.get(m_cryptoExchanged.getName());
        }
         
        float cryptoTransfer = m_cryptoExchanged.getQuantity();
        float newCryptoAmount = cryptoAmount - cryptoTransfer;

        sourceWallet.put(m_currencyDestination.getName(), newFiatAmount);
        sourceWallet.put(m_cryptoExchanged.getName(), newCryptoAmount);

        /////// Destination wallet transfer

        Map<String, Float> destinationWallet = m_orderDestination.getWallet();

        // Adding money in the wallet for the currency
        fiatAmount = 0f;
        if (destinationWallet.containsKey(m_currencySource.getName()))
        {
            fiatAmount = destinationWallet.get(m_currencySource.getName());
        }
        
        fiatTransfer = m_currencySource.getFinalValue();
        newFiatAmount = fiatAmount - fiatTransfer;

        // Reducing crypto from the same wallet
        cryptoAmount = 0f;
        if (destinationWallet.containsKey(m_cryptoExchanged.getName()))
        {
            cryptoAmount = destinationWallet.get(m_cryptoExchanged.getName());
        }
        
        // cryptoTransfer = m_cryptoExchanged.getQuantity();
        newCryptoAmount = cryptoAmount + cryptoTransfer;
        destinationWallet.put(m_currencySource.getName(), newFiatAmount);
        destinationWallet.put(m_cryptoExchanged.getName(), newCryptoAmount);
    }
}
