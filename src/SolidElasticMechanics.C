//* all reserve by SuQingji
//* suqj5@mail2.sysu.edu.cn

#include "SolidElasticMechanics.h"

registerMooseObject("huskyApp", SolidElasticMechanics);

InputParameters
SolidElasticMechanics::validParams()
{
    InputParameters params = Kernel::validParams();
    params.addRequiredParam<unsigned>("component", "compoent");
    return params;
}

SolidElasticMechanics::SolidElasticMechanics(const InputParameters &parameters)
    : Kernel(parameters),
      _G(getMaterialProperty<Real>("G")),
      _lambda(getMaterialProperty<Real>("lambda")),
      _component(getParam<unsigned>("component"))

{
}

Real SolidElasticMechanics::computeQpResidual()
{
    Real value = 0.;

    value = _G[_qp] * _grad_u[_qp] * _grad_test[_i][_qp] +
            (_lambda[_qp] + _G[_qp]) *
                (_grad_u[_qp](0) + _grad_u[_qp](1) + _grad_u[_qp](2)) * _grad_test[_i][_qp](_component);

    return value;
}

Real SolidElasticMechanics::computeQpJacobian()
{
    Real jac = 0.;

    jac = _G[_qp] * _grad_phi[_j][_qp] * _grad_test[_i][_qp] +
          (_lambda[_qp] + _G[_qp]) *
              (_grad_phi[_j][_qp](0) + _grad_phi[_j][_qp](1) + _grad_phi[_j][_qp](2)) * _grad_test[_i][_qp](_component);

    return jac;
}
