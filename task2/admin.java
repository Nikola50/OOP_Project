public class admin extends user
{
    public admin(String username, String password)
    {
        super(username, password);
        m_accountActivated = true;
    }

    // Is there need for it to be boolean?
    public void approveUser(trader unapprovedTrader)
    {
        if (unapprovedTrader != null)
        {
            unapprovedTrader.activateAccount();
        }
    }
}
