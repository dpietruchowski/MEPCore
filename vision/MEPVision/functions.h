#ifndef FUNTIONS_H
#define FUNTIONS_H

#include "image.h"
#include "utils/types.h"

using Args = mep::Args<Image>;

Image erosion(const Args &src);
Image dilation(const Args &src);
Image open(const Args &src);
Image close(const Args &src);
Image blackHat(const Args &src);
Image gradient(const Args &src);
Image bitwiseAnd(const Args& src);
Image bitwiseXor(const Args& src);
Image bitwiseOr(const Args& src);
Image bitwiseNot(const Args& src);
Image absDiff(const Args& src);
Image addF(const Args& src);
Image minF(const Args& src);
Image maxF(const Args& src);
Image diff(const Args& src);
Image recall(const Args& src);
Image fillHoles(const Args& src);
Image borderConnected(const Args& src);
Image borderDisconnected(const Args& src);

#endif // FUNTIONS_H
