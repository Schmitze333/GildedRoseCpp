#include "GildedRose.h"

void Item::updateNormalItem()
{
  if (quality == 0)
    return;

  quality -= 1;

  if (sellIn <= 0)
    quality -= 1;

  sellIn -= 1;
}

void Item::updateAgedBrie()
{
  const int MaxQuality{ 50 };

  sellIn -= 1;
  if (quality == MaxQuality)
    return;

  quality += 1;
  if (sellIn < 0 && quality < MaxQuality)
    quality += 1;
}

void Item::updateSulfuras()
{
  return;
}

void Item::updateBackstagePass()
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

void Item::update()
{
  if (name == "NORMAL ITEM") {
    updateNormalItem();
    return;
  } 
  else if (name == "Aged Brie") {
    updateAgedBrie();
    return;
  }
  else if (name == "Sulfuras, Hand of Ragnaros") {
    updateSulfuras();
    return;
  }
  else if (name == "Backstage passes to a TAFKAL80ETC concert") {
    updateBackstagePass();
    return;
  }
}

void GildedRose::updateQuality() 
{
    for (auto& item : _items)
    {
      item.update();
    }
}
