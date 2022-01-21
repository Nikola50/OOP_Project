public class limitOrder extends order
{
    private float m_limitPrice = 0f;

    public limitOrder(user source, user destination, fiat sourceCurrency, fiat destinationCurrency, crypto cryptoExchanged)
    {
        super(source, destination, sourceCurrency, destinationCurrency, cryptoExchanged);
        m_limitedOrder = true;
    }

    public float getLimitPrice()
    {
        return m_limitPrice;
    }
    
}