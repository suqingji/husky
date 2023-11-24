//* all reserve by SuQingji
//* suqj5@mail2.sysu.edu.cn

#pragma once

#include "IntegratedBC.h"

class PressureLoadBC : public IntegratedBC
{
public:
    static InputParameters validParams();

    PressureLoadBC(const InputParameters &parameters);

protected:
    virtual Real computeQpResidual();

    const Real &_value;

    const MaterialProperty<Real> &_G;
    const MaterialProperty<Real> &_E;
    const MaterialProperty<Real> &_lambda;

    unsigned _component;
};
