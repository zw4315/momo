#ifndef SERVICE_MARK_MASK_H_
#define SERVICE_MARK_MASK_H_

#include <cstdint>

using Mask = uint64_t;

// TODO: 未来加上范围校验
inline void SetBit(Mask& mask, int idx) { mask |= (Mask(1) << idx); }

inline bool TestBit(Mask mask, int idx) {
  return (mask & (Mask(1) << idx)) != 0;
}

inline void ClearBit(Mask& mask, int idx) { mask &= ~(Mask(1) << idx); }

inline bool Any(Mask mask) { return mask != 0; }

#endif  // SERVICE_MARK_MASK_H_
