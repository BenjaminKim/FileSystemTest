#pragma once

template<typename BitType>
class BitCombinator
{
public:
    BitCombinator()
        : allBit_(0)
        , allRawBit_(0)
    {}

    bool AddAllSingleBit(BitType bit)
    {
        for(BitType b = 1; bit; b <<= 1, bit >>= 1)
        {
            if(bit & 1)
            {
                if(!AddBit(b))
                {
                    return false;
                }
            }
        }
        return true;
    }

    bool AddBit(BitType bit)
    {
        if(allBit_ & bit)
        {
            return false;
        }
        allBit_ |= bit;
        allRawBit_ |= (BitType)1 << vBit_.size();
        vBit_.push_back(bit);
        return true;
    }

    BitType Next(BitType bit)
    {
        BitType rawBit(0);
        BitType checkBit(0);
        size_t count = vBit_.size();
        for(size_t x = 0; x < count; ++x)
        {
            BitType& b = vBit_[x];
            if((bit & b) == b)
            {
                rawBit |= (BitType)1 << x;
                checkBit |= b;

                if(checkBit == bit)
                {
                    break;
                }
            }
        }

        rawBit = (rawBit == allRawBit_) ? 0 : rawBit + 1;
        BitType nextBit(0);
        for(size_t x = 0; rawBit; ++x, rawBit >>= 1)
        {
            if(rawBit & 1)
            {
                nextBit |= vBit_[x];
            }
        }

        return nextBit;
    }

private:
    BitType allBit_;
    BitType allRawBit_;
    std::vector<BitType> vBit_;
};
