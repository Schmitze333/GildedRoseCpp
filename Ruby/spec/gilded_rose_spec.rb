require 'gilded_rose'

RSpec.describe GildedRose do
  def updated_item
    gilded_rose.items.first
  end

  let(:gilded_rose) { GildedRose.new([item]) }

  let(:initial_sell_in) { 5 }
  let(:initial_quality) { 10 }

  before { gilded_rose.update_quality }

  context 'with normal item' do
    let(:item) do
      GildedRose::Item.new('Normal Item', initial_sell_in, initial_quality)
    end

    context 'when before sell date' do
      it 'has a sell in decrease of 1' do
        expect(updated_item.sell_in).to eq(initial_sell_in - 1)
      end

      it 'decreases in quality by 1' do
        expect(updated_item.quality).to eq(initial_quality - 1)
      end
    end

    context 'when on sell date' do
      let(:initial_sell_in) { 0 }

      it 'has a sell in decrease of 1' do
        expect(updated_item.sell_in).to eq(initial_sell_in - 1)
      end

      it 'decreases in quality by 2' do
        expect(updated_item.quality).to eq(initial_quality - 2)
      end
    end

    context 'when after sell date' do
      let(:initial_sell_in) { -10 }

      it 'has a sell in decrease of 1' do
        expect(updated_item.sell_in).to eq(initial_sell_in - 1)
      end

      it 'decreases in quality by 2' do
        expect(updated_item.quality).to eq(initial_quality - 2)
      end
    end

    context 'when zero quality is reached' do
      let(:initial_quality) { 0 }

      it 'stays with zero quality' do
        expect(updated_item.quality).to eq 0
      end
    end
  end

  context 'with Aged Brie' do
    let(:item) do
      GildedRose::Item.new('Aged Brie', initial_sell_in, initial_quality)
    end

    context 'when before sell date' do
      it 'has a sell in decrease of 1' do
        expect(updated_item.sell_in).to eq(initial_sell_in - 1)
      end

      it 'increases in quality by 1' do
        expect(updated_item.quality).to eq(initial_quality + 1)
      end
    end

    context 'when on sell date' do
      let(:initial_sell_in) { 0 }

      it 'has a sell in decrease of 1' do
        expect(updated_item.sell_in).to eq(initial_sell_in - 1)
      end

      it 'increases in quality by 2' do
        expect(updated_item.quality).to eq(initial_quality + 2)
      end
    end

    context 'when on sell date having nearly maximal quality' do
      let(:initial_sell_in) { 0 }
      let(:initial_quality) { 49 }

      it 'has a sell in decrease of 1' do
        expect(updated_item.sell_in).to eq(initial_sell_in - 1)
      end

      it 'has a quality of 50' do
        expect(updated_item.quality).to eq(50)
      end
    end

    context 'when on sell date having maximal quality' do
      let(:initial_sell_in) { 0 }
      let(:initial_quality) { 50 }

      it 'has a sell in decrease of 1' do
        expect(updated_item.sell_in).to eq(initial_sell_in - 1)
      end

      it 'stays at quality of 50' do
        expect(updated_item.quality).to eq(50)
      end
    end

    context 'when after sell date' do
      let(:initial_sell_in) { -10 }

      it 'has a sell in decrease of 1' do
        expect(updated_item.sell_in).to eq(initial_sell_in - 1)
      end

      it 'increases in quality by 2' do
        expect(updated_item.quality).to eq(initial_quality + 2)
      end
    end

    context 'when after sell date having maximal quality' do
      let(:initial_sell_in) { -10 }
      let(:initial_quality) { 50 }

      it 'has a sell in decrease of 1' do
        expect(updated_item.sell_in).to eq(initial_sell_in - 1)
      end

      it 'stays at quality of 50' do
        expect(updated_item.quality).to eq(50)
      end
    end
  end

  context 'with Sulfuras' do
    let(:initial_quality) { 80 }
    let(:item) do
      GildedRose::Item.new(
        'Sulfuras, Hand of Ragnaros',
        initial_sell_in,
        initial_quality
      )
    end

    context 'when before sell date' do
      it 'has no sell in decrease' do
        expect(updated_item.sell_in).to eq(initial_sell_in)
      end

      it 'keeps its quality' do
        expect(updated_item.quality).to eq(initial_quality)
      end
    end

    context 'when on sell date' do
      let(:initial_sell_in) { 0 }

      it 'has no sell in decrease' do
        expect(updated_item.sell_in).to eq(initial_sell_in)
      end

      it 'keeps its quality' do
        expect(updated_item.quality).to eq(initial_quality)
      end
    end

    context 'when after sell date' do
      let(:initial_sell_in) { -10 }

      it 'has no sell in decrease' do
        expect(updated_item.sell_in).to eq(initial_sell_in)
      end

      it 'keeps its quality' do
        expect(updated_item.quality).to eq(initial_quality)
      end
    end
  end

  context 'with Backstage Pass' do
    let(:item) do
      GildedRose::Item.new(
        'Backstage passes to a TAFKAL80ETC concert',
        initial_sell_in,
        initial_quality
      )
    end

    context 'when long before sell date' do
      let(:initial_sell_in) { 11 }

      it 'has a sell in decrease of 1' do
        expect(updated_item.sell_in).to eq(initial_sell_in - 1)
      end

      it 'increases in quality by 1' do
        expect(updated_item.quality).to eq(initial_quality + 1)
      end

      context 'when maximum quality is reached' do
        let(:initial_quality) { 50 }

        it 'has a sell in decrease of 1' do
          expect(updated_item.sell_in).to eq(initial_sell_in - 1)
        end

        it 'does not increase in quality further' do
          expect(updated_item.quality).to eq(initial_quality)
        end
      end
    end

    context 'when medium close to sell date (upper bound)' do
      let(:initial_sell_in) { 10 }

      it 'has a sell in decrease of 1' do
        expect(updated_item.sell_in).to eq(initial_sell_in - 1)
      end

      it 'increases in quality by 2' do
        expect(updated_item.quality).to eq(initial_quality + 2)
      end

      context 'when maximal quality is reached' do
        let(:initial_quality) { 50 }

        it 'has a sell in decrease of 1' do
          expect(updated_item.sell_in).to eq(initial_sell_in - 1)
        end

        it 'does not increase in quality further' do
          expect(updated_item.quality).to eq(initial_quality)
        end
      end
    end

    context 'when medium close to sell date (lower bound)' do
      let(:initial_sell_in) { 6 }

      it 'has a sell in decrease of 1' do
        expect(updated_item.sell_in).to eq(initial_sell_in - 1)
      end

      it 'increases in quality by 2' do
        expect(updated_item.quality).to eq(initial_quality + 2)
      end

      context 'when maximal quality is reached' do
        let(:initial_quality) { 50 }

        it 'has a sell in decrease of 1' do
          expect(updated_item.sell_in).to eq(initial_sell_in - 1)
        end

        it 'does not increase in quality further' do
          expect(updated_item.quality).to eq(initial_quality)
        end
      end
    end

    context 'when very close to sell date (upper bound)' do
      let(:initial_sell_in) { 5 }

      it 'has a sell in decrease of 1' do
        expect(updated_item.sell_in).to eq(initial_sell_in - 1)
      end

      it 'increases in quality by 3' do
        expect(updated_item.quality).to eq(initial_quality + 3)
      end

      context 'when maximal quality is reached' do
        let(:initial_quality) { 50 }

        it 'has a sell in decrease of 1' do
          expect(updated_item.sell_in).to eq(initial_sell_in - 1)
        end

        it 'does not increase in quality further' do
          expect(updated_item.quality).to eq(initial_quality)
        end
      end
    end

    context 'when very close to sell date (lower bound)' do
      let(:initial_sell_in) { 1 }

      it 'has a sell in decrease of 1' do
        expect(updated_item.sell_in).to eq(initial_sell_in - 1)
      end

      it 'increases in quality by 3' do
        expect(updated_item.quality).to eq(initial_quality + 3)
      end

      context 'when maximal quality is reached' do
        let(:initial_quality) { 50 }

        it 'has a sell in decrease of 1' do
          expect(updated_item.sell_in).to eq(initial_sell_in - 1)
        end

        it 'does not increase in quality further' do
          expect(updated_item.quality).to eq(initial_quality)
        end
      end
    end

    context 'when on sell date' do
      let(:initial_sell_in) { 0 }

      it 'has a sell in decrease of 1' do
        expect(updated_item.sell_in).to eq(initial_sell_in - 1)
      end

      it 'has quality of 0' do
        expect(updated_item.quality).to eq(0)
      end
    end

    context 'when after sell date' do
      let(:initial_sell_in) { -10 }

      it 'has a sell in decrease of 1' do
        expect(updated_item.sell_in).to eq(initial_sell_in - 1)
      end

      it 'has quality of 0' do
        expect(updated_item.quality).to eq(0)
      end
    end
  end

  xcontext 'with Conjured Mana Cake', pending: 'new feature request' do
    let(:item) do
      GildedRose::Item.new(
        'Conjured Mana Cake',
        initial_sell_in,
        initial_quality
      )
    end

    context 'when before sell date' do
      it 'has a sell in decrease of 1' do
        expect(updated_item.sell_in).to eq(initial_sell_in - 1)
      end

      it 'decreases in quality by 2' do
        expect(updated_item.quality).to eq(initial_quality - 2)
      end

      context 'when zero quality is reached' do
        let(:initial_quality) { 0 }

        it 'has a sell in decrease of 1' do
          expect(updated_item.sell_in).to eq(initial_sell_in - 1)
        end

        it 'has quality of 0' do
          expect(updated_item.quality).to eq(0)
        end
      end
    end

    context 'when on sell date' do
      let(:initial_sell_in) { 0 }

      it 'has a sell in decrease of 1' do
        expect(updated_item.sell_in).to eq(initial_sell_in - 1)
      end

      it 'decreases in quality by 4' do
        expect(updated_item.quality).to eq(initial_quality - 4)
      end

      context 'when zero quality is reached' do
        let(:initial_quality) { 0 }

        it 'has a sell in decrease of 1' do
          expect(updated_item.sell_in).to eq(initial_sell_in - 1)
        end

        it 'has quality of 0' do
          expect(updated_item.quality).to eq(0)
        end
      end
    end
  end
end
