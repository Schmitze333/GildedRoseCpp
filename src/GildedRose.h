#include <string>
#include <vector>
#include <memory>

class Item
{
  void updateNormalItem();
  void updateAgedBrie();
  void updateSulfuras();
  void updateBackstagePass();

public:
  static std::shared_ptr<Item> CreateItem(const std::string& name, const int sellIn, const int quality);
  std::string name;
  int sellIn;
  int quality;
  Item(std::string name, int sellIn, int quality) : name(name), sellIn(sellIn), quality(quality) 
  {}

  virtual void update();
};

class NormalItem : public Item
{
public:
  NormalItem(const int sellIn, const int quality)
    : Item("NORMAL ITEM", sellIn, quality) {}

  void update() override;
};

class AgedBrie : public Item
{
public:
  AgedBrie(const int sellIn, const int quality)
    : Item("Aged Brie", sellIn, quality) {}

  void update() override;
};

class GildedRose
{
  std::vector<std::shared_ptr<Item> > _items;

public:
  GildedRose() {}
  
  void updateQuality();
  void addItem(std::shared_ptr<Item> item) { _items.emplace_back(item); }
  std::shared_ptr<Item> getItem(const int index) const { return _items.at(index); }
};
