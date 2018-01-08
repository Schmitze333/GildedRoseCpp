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

  if (item.name != "Aged Brie" && item.name != "Backstage passes to a TAFKAL80ETC concert")
  {
    if (item.quality > 0)
    {
      if (item.name != "Sulfuras, Hand of Ragnaros")
      {
        item.quality = item.quality - 1;
      }
    }
  }
  else
  {
    if (item.quality < 50)
    {
      item.quality = item.quality + 1;

      if (item.name == "Backstage passes to a TAFKAL80ETC concert")
      {
        if (item.sellIn < 11)
        {
          if (item.quality < 50)
          {
            item.quality = item.quality + 1;
          }
        }

        if (item.sellIn < 6)
        {
          if (item.quality < 50)
          {
            item.quality = item.quality + 1;
          }
        }
      }
    }
  }

  if (item.name != "Sulfuras, Hand of Ragnaros")
  {
    item.sellIn = item.sellIn - 1;
  }

  if (item.sellIn < 0)
  {
    if (item.name != "Aged Brie")
    {
      if (item.name != "Backstage passes to a TAFKAL80ETC concert")
      {
        if (item.quality > 0)
        {
          if (item.name != "Sulfuras, Hand of Ragnaros")
          {
            item.quality = item.quality - 1;
          }
        }
      }
      else
      {
        item.quality = item.quality - item.quality;
      }
    }
    else
    {
      if (item.quality < 50)
      {
        item.quality = item.quality + 1;
      }
    }
  }
}

void GildedRose::updateQuality() 
{
    for (auto& item : _items)
    {
      updateItem(item);
    }
}
