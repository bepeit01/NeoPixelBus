/*-------------------------------------------------------------------------
Lpd8806ColorFeatures provides feature classes to describe color order and
color depth for NeoPixelBus template class when used with DotStar like chips

Written by Michael C. Miller.

I invest time and resources providing this open source code,
please support me by dontating (see https://github.com/Makuna/NeoPixelBus)

-------------------------------------------------------------------------
This file is part of the Makuna/NeoPixelBus library.

NeoPixelBus is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as
published by the Free Software Foundation, either version 3 of
the License, or (at your option) any later version.

NeoPixelBus is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with NeoPixel.  If not, see
<http://www.gnu.org/licenses/>.
-------------------------------------------------------------------------*/
#pragma once

class Melinera5ElementsNoSettings
{
public:
    typedef NeoNoSettings SettingsObject;
    static const size_t SettingsSize = 0;

    static void applySettings([[maybe_unused]] uint8_t* pData, [[maybe_unused]] size_t sizeData, [[maybe_unused]] const SettingsObject& settings)
    {
    }

    static uint8_t* pixels([[maybe_unused]] uint8_t* pData, [[maybe_unused]] size_t sizeData)
    {
        return pData;
    }

    static const uint8_t* pixels([[maybe_unused]] const uint8_t* pData, [[maybe_unused]] size_t sizeData)
    {
        return pData;
    }
};

class Melinera5Elements : public Melinera5ElementsNoSettings
{
public:
    static const size_t PixelSize = 4; 


    static uint8_t* getPixelAddress(uint8_t* pPixels, uint16_t indexPixel)
    {
        return pPixels + indexPixel * PixelSize;
    }
    static const uint8_t* getPixelAddress(const uint8_t* pPixels, uint16_t indexPixel)
    {
        return pPixels + indexPixel * PixelSize;
    }

    static void replicatePixel(uint8_t* pPixelDest, const uint8_t* pPixelSrc, uint16_t count)
    {
        uint8_t* pEnd = pPixelDest + (count * PixelSize);
        while (pPixelDest < pEnd)
        {
            *pPixelDest++ = pPixelSrc[0];
            *pPixelDest++ = pPixelSrc[1];
            *pPixelDest++ = pPixelSrc[2];
            *pPixelDest++ = pPixelSrc[3];
        }
    }

    static void movePixelsInc(uint8_t* pPixelDest, const uint8_t* pPixelSrc, uint16_t count)
    {
        uint8_t* pEnd = pPixelDest + (count * PixelSize);
        while (pPixelDest < pEnd)
        {
            *pPixelDest++ = *pPixelSrc++;
            *pPixelDest++ = *pPixelSrc++;
            *pPixelDest++ = *pPixelSrc++;
            *pPixelDest++ = *pPixelSrc++;
        }
    }

    static void movePixelsInc_P(uint8_t* pPixelDest, PGM_VOID_P pPixelSrc, uint16_t count)
    {
        uint8_t* pEnd = pPixelDest + (count * PixelSize);
        const uint8_t* pSrc = (const uint8_t*)pPixelSrc;
        while (pPixelDest < pEnd)
        {
            *pPixelDest++ = pgm_read_byte(pSrc++);
            *pPixelDest++ = pgm_read_byte(pSrc++);
            *pPixelDest++ = pgm_read_byte(pSrc++);
            *pPixelDest++ = pgm_read_byte(pSrc++);
        }
    }

    static void movePixelsDec(uint8_t* pPixelDest, const uint8_t* pPixelSrc, uint16_t count)
    {
        uint8_t* pDestBack = pPixelDest + (count * PixelSize);
        const uint8_t* pSrcBack = pPixelSrc + (count * PixelSize);
        while (pDestBack > pPixelDest)
        {
            *--pDestBack = *--pSrcBack;
            *--pDestBack = *--pSrcBack;
            *--pDestBack = *--pSrcBack;
            *--pDestBack = *--pSrcBack;
        }
    }

    typedef RgbwColor ColorObject;
};

class  MelineraWRGBFeature : public Melinera5Elements
{
public:
    static void applyPixelColor(uint8_t* pPixels, uint16_t indexPixel, ColorObject color)
    {
        uint8_t* p = getPixelAddress(pPixels, indexPixel);
        *p++ = (color.W);
        *p++ = (color.R);
        *p++ = (color.G);
        *p = (color.B);
    }

    static ColorObject retrievePixelColor(const uint8_t* pPixels, uint16_t indexPixel)
    {
        ColorObject color;
        const uint8_t* p = getPixelAddress(pPixels, indexPixel);

        color.W = (*p++);
        color.R = (*p++);
        color.G = (*p++);
        color.B = (*p);

        return color;
    }

    static ColorObject retrievePixelColor_P(PGM_VOID_P pPixels, uint16_t indexPixel)
    {
        ColorObject color;
        const uint8_t* p = getPixelAddress((const uint8_t*)pPixels, indexPixel);

        color.W = (pgm_read_byte(p++));
        color.R = (pgm_read_byte(p++));
        color.G = (pgm_read_byte(p++));
        color.B = (pgm_read_byte(p));

        return color;
    }

};