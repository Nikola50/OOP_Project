public class trader extends user
{
    public trader(String username, String password)
    {
        super(username, password);
    }

   public void assignCrypto(crypto toAdd)
   {
    if (m_wallet.containsKey(toAdd.getName()))
    {
        // Updating the existing balance
        float currentValue = m_wallet.get(toAdd.getName());
        float newValue = currentValue + toAdd.getQuantity();
        m_wallet.replace(toAdd.getName(), newValue);
    }
    else
    {
        m_wallet.put(toAdd.getName(),(float)toAdd.getQuantity());
    }
   }

    
}
