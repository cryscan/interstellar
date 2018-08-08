//
// Created by lepet on 8/6/2018.
//

#ifndef P3_OUTLINE_H
#define P3_OUTLINE_H

#include <objects/object.h>


class outline : public object {
public:
    void render(int pass) override;

};


#endif //P3_OUTLINE_H
