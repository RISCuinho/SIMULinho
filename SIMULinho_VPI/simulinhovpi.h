#ifndef SIMULINHOVPI_H
#define SIMULINHOVPI_H

#include "simulinho_lib_global.h"

class SIMULinhoVPI
{

    public:
        static SIMULinhoVPI& getInstance()
        {
            // a título de estudo algumas anotações.
            // Double-Checked Locking Pattern (DCLP); see Douglas C. Schmidt et al.,
            // "Double-Checked Locking" and Douglas C. Schmidt et al.,
            // Pattern-Oriented Software Architecture, Volume 2
            //
            static SIMULinhoVPI instance; // Guaranteed to be destroyed.
                                  // Instantiated on first use.
            return instance;
        }
    private:
        SIMULinhoVPI(){}                    // Constructor? (the {} brackets) are needed here.

        // C++ 03
        // ========
        // Don't forget to declare these two. You want to make sure they
        // are inaccessible(especially from outside), otherwise, you may accidentally get copies of
        // your singleton appearing.
        SIMULinhoVPI(SIMULinhoVPI const&);              // Don't Implement
        void operator=(SIMULinhoVPI const&); // Don't implement

        // C++ 11
        // =======
        // We can use the better technique of deleting the methods
        // we don't want.
    public:
        SIMULinhoVPI(SIMULinhoVPI const&)               = delete;
        void operator=(SIMULinhoVPI const&)  = delete;

        // Note: Scott Meyers mentions in his Effective Modern
        //       C++ book, that deleted functions should generally
        //       be public as it results in better error messages
        //       due to the compilers behavior to check accessibility
        //       before deleted status
};

#endif // SIMULINHOVPI_H
