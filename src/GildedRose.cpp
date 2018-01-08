#include "GildedRose.h"

void GildedRose::updateNormalItem(Item& item)
{
  if (item.quality == 0)
    return;

  item.quality -= 1;

  if (item.sellIn <= 0)
    item.quality -= 1;

  item.sellIn -= 1;
}

void GildedRose::updateAgedBrie(Item& item)
{
  const int MaxQuality{ 50 };

  item.sellIn -= 1;
  if (item.quality == MaxQuality)
    return;

  item.quality += 1;
  if (item.sellIn < 0 && item.quality < MaxQuality)
    item.quality += 1;
}

void GildedRose::updateSulfuras(Item& item)
{
  return;
}

void GildedRose::updateBackstagePass(Item& item)
{
  item.sellIn -= 1;

  if (item.quality == 50)
    return;

  if (item.sellIn < 0) {
    item.quality = 0;
    return;
  }

  item.quality += 1;

  if (item.sellIn < 10)
    item.quality += 1;

  if (item.sellIn < 5)
    item.quality += 1;
}

void GildedRose::updateItem(Item& item)
{
  if (item.name == "NORMAL ITEM") {
    updateNormalItem(item);
    return;
  } 
  else if (item.name == "Aged Brie") {
    updateAgedBrie(item);
    return;
  }
  else if (item.name == "Sulfuras, Hand of Ragnaros") {
    updateSulfuras(item);
    return;
  }
  else if (item.name == "Backstage passes to a TAFKAL80ETC concert") {
    updateBackstagePass(item);
    return;
  }
}

void GildedRose::updateQuality() 
{
    for (auto& item : _items)
    {
      updateItem(item);
    }
}
