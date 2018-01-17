#include <string>
#include <vector>
#include <memory>

class Item
{
public:
  static std::shared_ptr<Item> CreateItem(const std::string& name, const int sellIn, const int quality);
  std::string name{ "" };
  int sellIn;
  int quality;
  Item(int sellIn, int quality) : sellIn(sellIn), quality(quality) 
  {}

  virtual void update() {};
};

class NormalItem : public Item
{
public:
  static const std::string Name;

  NormalItem(const int sellIn, const int quality)
    : Item(sellIn, quality) { name = Name; }

  void update() override;
};

class AgedBrie : public Item
{
  const int MaxQuality{ 50 };

public:
  static const std::string Name;

  AgedBrie(const int sellIn, const int quality)
    : Item(sellIn, quality) { name = Name; }

  void update() override;
};

class BackstagePass : public Item
{
  const int MaxQuality{ 50 };
  std::vector<int> _qualityThresholds{5, 10};

public:
  static const std::string Name;

  BackstagePass(const int sellIn, const int quality)
    : Item(sellIn, quality) {}

  void update() override;
};

class ConjuredMana : public Item
{
public:
  static const std::string Name;

  ConjuredMana(const int sellIn, const int quality)
    : Item(sellIn, quality) { name = Name; }

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
