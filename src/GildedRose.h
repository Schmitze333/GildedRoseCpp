#include <string>
#include <vector>

class Item
{
  void updateNormalItem();
  void updateAgedBrie();
  void updateSulfuras();
  void updateBackstagePass();

  public:
    std::string name;
    int sellIn;
    int quality;
    Item(std::string name, int sellIn, int quality) : name(name), sellIn(sellIn), quality(quality) 
    {}

    void update();
};

class GildedRose
{
  std::vector<Item> _items;

  public:
    GildedRose() {}
    
    void updateQuality();
    void addItem(const Item&& item) { _items.emplace_back(item); }
    Item getItem(const int index) const { return _items.at(index); }
};
