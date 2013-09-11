#pragma once

#include <limits>


template<class DataType, class MomentType, class ResultType>
class Statistics
{
public:
    Statistics(DataType min = (std::numeric_limits<DataType>::min)(), DataType max = (std::numeric_limits<DataType>::max)())
        : count_(0)
        , min_(max)
        , max_(min)
        , sum_(0)
        , sum2_(0)
    {
    }

    void clear()
    {
        count_ = 0;
        min_ = (std::numeric_limits<DataType>::max)();
        max_ = (std::numeric_limits<DataType>::min)();
        sum_ = 0;
        sum2_ = 0;
    }

    void InsertData(DataType value)
    {
        ++count_;
        if(value > max_)
        {
            max_ = value;
        }
        if(value < min_ && value > 0)
        {
            min_ = value;
        }
        sum_ += static_cast<MomentType>(value);
        sum2_ += static_cast<MomentType>(value) * static_cast<MomentType>(value);
    }

    size_t Count() const
    {
        return count_;
    }
    
    DataType Max() const
    {
        return max_;
    }
    
    DataType Min() const
    {
        return min_;
    }
    
    ResultType Avg() const
    {
        if(count_ == 0)
        {
            return 0;
        }
        return static_cast<ResultType>(sum_) / static_cast<ResultType>(count_);
    }
    
    MomentType Sum() const
    {
        return sum_;
    }
    
    ResultType Variance() const
    {
        if(count_ == 0)
        {
            return 0;
        }
        ResultType avg = Avg();
        return static_cast<ResultType>(sum2_) / static_cast<ResultType>(count_) - avg * avg;
    }
    
    ResultType StdDev() const
    {
        return static_cast<ResultType>(sqrt(Variance()));
    }

private:
    size_t count_;
    DataType max_;
    DataType min_;
    MomentType sum_;
    MomentType sum2_;
};

typedef Statistics<double, double, double> ApiStatistics;