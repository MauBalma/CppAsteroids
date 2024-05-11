#pragma once

namespace Math
{
    struct float2
    {
        float x;
        float y;
            
        float2 operator+(const float2& value) const;
        void operator+=(const float2& value);
        
        float2 operator*(const float& value) const;
        void operator*=(const float& value);
        
        float2 operator/(const float& value) const;
        void operator/=(const float& value);
    };

    inline float2 float2::operator+(const float2& value) const
    {
        return float2{x + value.x, y + value.y};
    }

    inline void float2::operator+=(const float2& value)
    {
        this->x += value.x;
        this->y += value.y;
    }

    inline float2 float2::operator*(const float& value) const
    {
        return float2{x * value, y * value};
    }

    inline void float2::operator*=(const float& value)
    {
        this->x *= value;
        this->y *= value;
    }

    inline float2 float2::operator/(const float& value) const
    {
        return float2{x / value, y / value};
    }

    inline void float2::operator/=(const float& value)
    {
        this->x /= value;
        this->y /= value;
    }
}

