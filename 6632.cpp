#include <string>

using std::string;

class Stock
{

  public:
    Stock(string symbol, string name) : symbol(symbol), name(name)
    {
    }
    string getSymbol() { return symbol; }
    string getName() { return name; }
    double getPreviousClosingPrice() { return previousClosingPrice; }
    double getCurrentPrice() { return currentPrice; }
    void setPreviousClosingPrice(double previousClosingPrice) { this->previousClosingPrice = previousClosingPrice; }
    void setCurrentPrice(double currentPrice) { this->currentPrice = currentPrice; }
    double changePercent() { return currentPrice / previousClosingPrice; }

  private:
    string symbol;
    string name;
    double previousClosingPrice;
    double currentPrice;
};