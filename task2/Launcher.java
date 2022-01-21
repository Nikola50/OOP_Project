import java.util.Set;

public class Launcher
{
    public static void main (String[] args)
    {
        // Creating an admin and a trader
        admin admin1 = new admin("plase", "plase2");
        trader trader1 = new trader("milko", "stojko");
        trader trader2 = new trader("micko", "stocko");
        
        // Approving trader profiles

        admin1.approveUser(trader1);
        admin1.approveUser(trader2);

        // Creating fiat currencies
        fiat euro_100 = new fiat("EUR", 100);
        fiat dollar_100 = new fiat("USD", 100);
        fiat dollar_50 = new fiat("USD", 50);
        fiat euro_200 = new fiat("EUR", 200);
        fiat dollar_200 = new fiat("USD", 200);
       
        ////// DEPOSIT MONEY FOR 2 TRADERS ///////

        trader2.depositFunds(euro_100);
        trader2.depositFunds(dollar_100);
        trader1.depositFunds(euro_200);
        trader1.depositFunds(dollar_200);

        printWallets(trader1, trader2);

        crypto bitcoin_10 = new crypto("BTC", 10);
        crypto bitcoin_5 = new crypto("BTC", 5);
        crypto etherium_5 = new crypto("ETH", 5);
        String bitcoinName = bitcoin_10.getName();
        String etheriumName = etherium_5.getName();  

        Set<String> cryptoCurrencyNames = Set.of(bitcoinName, etheriumName);

        /////// CREATE ORDERBOOK AND MATCHING ENGINE ///////

        orderbook myOrderbook = new orderbook(cryptoCurrencyNames);
        matchingEngine myMatchingEngine = new matchingEngine(myOrderbook);

        /////// CREATE ORDERS ///////

        trader2.assignCrypto(bitcoin_10);

        order buyOrder = new order(null, trader1, null, dollar_100, bitcoin_10);
        limitOrder sellOrder = new limitOrder(trader2, null, dollar_100, null, bitcoin_10);

        myMatchingEngine.processOrder(sellOrder);
        myMatchingEngine.processOrder(buyOrder);

        printWallets(trader1, trader2);

        order buyOrder2 = new order(null, trader2, null, dollar_50, bitcoin_5);
        limitOrder sellOrder2 = new limitOrder(trader1, null, dollar_50, null, bitcoin_5);

        myMatchingEngine.processOrder(sellOrder2);
        myMatchingEngine.processOrder(buyOrder2);

        printWallets(trader1, trader2);
    }

    private static void printWallets(trader trader1, trader trader2)
    {
        System.out.println("trader1 wallet: " + trader1.getWallet());
        System.out.println("trader2 wallet: " + trader2.getWallet()); 
    }
}
