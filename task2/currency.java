public class currency 
{
    protected String m_name = "";
    protected int m_quantity = 0;

    protected currency(String name, int quantity)
    {
        m_name = name;
        m_quantity = quantity;
    }

    protected String getName()
    {
        return m_name;
    }

    protected int getQuantity()
    {
        return m_quantity;
    }
}
