#include "service/rules.h"

Mask StartEndRule::Evaluate(const DateParts& day, TagRegistry& registry) {
  Mask mask = 0;
  if (day.iso == start_iso_) {
    SetBit(mask, registry.Index("Start"));
  }
  if (day.iso == end_iso_) {
    SetBit(mask, registry.Index("End"));
  }
  return mask;
}
