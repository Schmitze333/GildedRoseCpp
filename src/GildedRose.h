#include <string>
#include <vector>

class Item
{
  public:
    std::string name;
    int sellIn;
    int quality;
    Item(std::string name, int sellIn, int quality) : name(name), sellIn(sellIn), quality(quality) 
    {}
};

class GildedRose
{
  std::vector<Item> _items;

  void updateItem(Item& item);
  void updateNormalItem(Item& item);
  void updateAgedBrie(Item& item);
  void updateSulfuras(Item& item);

  public:
    GildedRose() {}
    
    void updateQuality();
    void addItem(const Item&& item) { _items.emplace_back(item); }
    Item getItem(const int index) const { return _items.at(index); }
};
