#include "max_n.h"

int max_n(ull devider, ull bound){
    ull result;
    if (devider > bound) {
        return 0;
    }
    for (ull i = bound; i > 0; i--) {
        if ((i % devider == 0)) {
            result = i;
            break;
        }
    }
    return result;
}
