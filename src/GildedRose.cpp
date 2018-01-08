#include "GildedRose.h"

void GildedRose::updateQuality() 
{
    for (int i = 0; i < _items.size(); i++)
    {
        if (_items[i].name != "Aged Brie" && _items[i].name != "Backstage passes to a TAFKAL80ETC concert")
        {
            if (_items[i].quality > 0)
            {
                if (_items[i].name != "Sulfuras, Hand of Ragnaros")
                {
                    _items[i].quality = _items[i].quality - 1;
                }
            }
        }
        else
        {
            if (_items[i].quality < 50)
            {
                _items[i].quality = _items[i].quality + 1;

                if (_items[i].name == "Backstage passes to a TAFKAL80ETC concert")
                {
                    if (_items[i].sellIn < 11)
                    {
                        if (_items[i].quality < 50)
                        {
                            _items[i].quality = _items[i].quality + 1;
                        }
                    }

                    if (_items[i].sellIn < 6)
                    {
                        if (_items[i].quality < 50)
                        {
                            _items[i].quality = _items[i].quality + 1;
                        }
                    }
                }
            }
        }

        if (_items[i].name != "Sulfuras, Hand of Ragnaros")
        {
            _items[i].sellIn = _items[i].sellIn - 1;
        }

        if (_items[i].sellIn < 0)
        {
            if (_items[i].name != "Aged Brie")
            {
                if (_items[i].name != "Backstage passes to a TAFKAL80ETC concert")
                {
                    if (_items[i].quality > 0)
                    {
                        if (_items[i].name != "Sulfuras, Hand of Ragnaros")
                        {
                            _items[i].quality = _items[i].quality - 1;
                        }
                    }
                }
                else
                {
                    _items[i].quality = _items[i].quality - _items[i].quality;
                }
            }
            else
            {
                if (_items[i].quality < 50)
                {
                    _items[i].quality = _items[i].quality + 1;
                }
            }
        }
    }
}
