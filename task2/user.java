import java.util.HashMap;
import java.util.Map;
import java.util.Set;

public class user
{
    protected Map<String, Float> m_wallet = new HashMap<String, Float>(); 
    protected String m_username = "";
    protected String m_password = "";
    protected boolean m_accountActivated = false;

    protected user(String username, String password)
    {
        m_password = password;
        m_username = username;
    }

    protected void activateAccount()
    {
        m_accountActivated = true;
    }

    protected String getUsername()
    {
        return m_username;
    }

    protected String getPassword()
    {
        return m_password;
    }

    protected boolean getAccountStatus()
    {
        return m_accountActivated;
    }

    // WITHDRAW FUNDS

    public Map<String, Float> getWallet()
    {
        if (!getAccountStatus())
        {
            return null;
        }

        return m_wallet;
    }

    public Set<String> getWalletCurrencies()
    {
        if (!getAccountStatus())
        {
            return null;
        }

        return m_wallet.keySet();
    }

    public void depositFunds(fiat currencyDetails)
    {
        if (!getAccountStatus())
        {
            return;
        }

        String currencyName = currencyDetails.getName();
        float valueToAdd = currencyDetails.getQuantity();
        
        // Checking if a wallet contains a currency balance
        // Updating the balance if it does, creating a new balance if it does not
        if (m_wallet.containsKey(currencyName))
        {
            // Updating the existing balance
            float currentValue = m_wallet.get(currencyName);
            float newValue = currentValue + valueToAdd;
            m_wallet.replace(currencyName, newValue);
        }
        else
        {
            m_wallet.put(currencyName, valueToAdd);
        }
    }
}