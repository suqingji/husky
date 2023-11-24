//* all reserve by SuQingji
//* suqj5@mail2.sysu.edu.cn

#pragma once

#include "Material.h"
#include "LinearInterpolation.h"

class ComputeOthers : public Material
{
public:
    ComputeOthers(const InputParameters &parameters);

    static InputParameters validParams();

protected:
    virtual void computeQpProperties() override;

private:
    MaterialProperty<Real> &_epsilon_x;
    MaterialProperty<Real> &_epsilon_y;
    MaterialProperty<Real> &_epsilon_xy;

    MaterialProperty<Real> &_sigma_x;
    MaterialProperty<Real> &_sigma_y;
    MaterialProperty<Real> &_sigma_xy;

    MaterialProperty<Real> &_Mises;

    MaterialProperty<Real> &_G;
    MaterialProperty<Real> &_lambda;

    MaterialProperty<Real> &_E;
    MaterialProperty<Real> &_mu;

    const VariableValue &_u;
    const VariableValue &_v;

    const VariableGradient &_grad_u;
    const VariableGradient &_grad_v;

};
