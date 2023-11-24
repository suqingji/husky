//* all reserve by SuQingji
//* suqj5@mail2.sysu.edu.cn

#pragma once

#include "Kernel.h"

class SolidElasticMechanics : public Kernel
{
public:
    static InputParameters validParams();

    SolidElasticMechanics(const InputParameters &parameters);

protected:
    virtual Real computeQpResidual() override;

    virtual Real computeQpJacobian() override;

    const MaterialProperty<Real> &_G;
    const MaterialProperty<Real> &_lambda;

    unsigned _component;
};
