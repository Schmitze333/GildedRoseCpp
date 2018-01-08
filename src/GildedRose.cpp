#include "GildedRose.h"

const std::string BackstagePass::Name = "Backstage passes to a TAFKAL80ETC concert";
const std::string AgedBrie::Name = "Aged Brie"; 
const std::string NormalItem::Name = "NORMAL ITEM"; 

std::shared_ptr<Item> Item::CreateItem(const std::string& name, const int sellIn, const int quality)
{
  if (name == NormalItem::Name)
    return std::make_shared<NormalItem>(sellIn, quality);
  else if (name == AgedBrie::Name)
    return std::make_shared<AgedBrie>(sellIn, quality);
  else if (name == BackstagePass::Name)
    return std::make_shared<BackstagePass>(sellIn, quality);

  return std::make_shared<Item>(sellIn, quality);
}

void NormalItem::update()
{
  if (quality == 0)
    return;

  quality -= 1;

  if (sellIn <= 0)
    quality -= 1;

  sellIn -= 1;
}

void AgedBrie::update()
{
  const int MaxQuality{ 50 };

  sellIn -= 1;
  if (quality == MaxQuality)
    return;

  quality += 1;
  if (sellIn < 0 && quality < MaxQuality)
    quality += 1;
}

void BackstagePass::update()
{
  sellIn -= 1;

  if (quality == 50)
    return;

  if (sellIn < 0) {
    quality = 0;
    return;
  }

  quality += 1;

  if (sellIn < 10)
    quality += 1;

  if (sellIn < 5)
    quality += 1;
}

void GildedRose::updateQuality() 
{
    for (auto& item : _items)
    {
      item->update();
    }
}
