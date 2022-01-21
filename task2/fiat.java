import java.util.HashMap;
import java.util.Map;

public class fiat extends currency
{
    float m_value = 0f;
    Map<String, Float> m_fiatDatabase = new HashMap<String, Float>(){
    {
        put("EUR", 1.0f);
        put("USD", 1.14f);
    }
    };

    public fiat(String name, int quantity)
    {
        super(name, quantity);
        
        m_value = m_fiatDatabase.get(name);
    }

    public float getValue()
    {
        return m_value;
    }

    public float getFinalValue()
    {
        return m_quantity * m_value;
    }

    
}
