#ifndef SIMULINHOVPI_H
#define SIMULINHOVPI_H

#include "simulinho.h"
#include <uuid/uuid.h>
#include <vpi_user.h>

#include "simulinho_lib_global.h"

#define SIMULINHO_INIT      (ICARUS_VPI_CONST PLI_BYTE8*)"init"
#define SIMULINHO_STOP      (ICARUS_VPI_CONST PLI_BYTE8*)"stop"
#define SIMULINHO_FINISH    (ICARUS_VPI_CONST PLI_BYTE8*)"finish"

/**
 * @brief The SIMULinhoVPI class
 */
class SIMULinhoVPI
{

    public:
        /**
         * @brief getInstance
         * @return
         */
        static SIMULinhoVPI* getInstance()
        {
            // a título de estudo algumas anotações.
            // Double-Checked Locking Pattern (DCLP); see Douglas C. Schmidt et al.,
            // "Double-Checked Locking" and Douglas C. Schmidt et al.,
            // Pattern-Oriented Software Architecture, Volume 2
            //
            static SIMULinhoVPI instance; // Guaranteed to be destroyed.
                                  // Instantiated on first use.
            return &instance;
        }

        /**
         * Inicializa comunicação com a interface gráfica, o serviço gráfico do
         * SIMUlinho já deve estar rodando.
         *
         * A chamada desta função deve ser única, com ela a comunicação com o
         * serviço de interface gráfica é estabelecida, o nome do projeto sendo
         * simulado é informado a interface que cria um UUID e prepara a
         * estrutura de armazenamento dos dados coletados referente a simulação.
         *
         * O UUID retornado é armazenado no singleton, cada instância de simulação
         * somente pode chamar uma unica vez o processo de inicialização.
         *
         * Caso o segundo parametro seja informado, deve ser o UUID já conhecido.
         * Com este UUID as estrutura de coletada do serviço gráfico será
         * reaproveitada.
         *
         * @brief init
         * @param rtlName
         * @param uuid
         */
        void init(char*,uuid_t);
        void stop(uuid_t);
        void finish(uuid_t);
    private:
        SIMULinhoVPI(){}                    // Constructor? (the {} brackets) are needed here.

        // C++ 03
        // ========
        // Don't forget to declare these two. You want to make sure they
        // are inaccessible(especially from outside), otherwise, you may accidentally get copies of
        // your singleton appearing.
        SIMULinhoVPI(SIMULinhoVPI const&);   // Don't Implement
        void operator=(SIMULinhoVPI const&); // Don't implement

        // C++ 11
        // =======
        // We can use the better technique of deleting the methods
        // we don't want.
    public:
        SIMULinhoVPI(SIMULinhoVPI *const)   = delete;
        void operator=(SIMULinhoVPI *const) = delete;

        // Note: Scott Meyers mentions in his Effective Modern
        //       C++ book, that deleted functions should generally
        //       be public as it results in better error messages
        //       due to the compilers behavior to check accessibility
        //       before deleted status
};

#endif // SIMULINHOVPI_H
