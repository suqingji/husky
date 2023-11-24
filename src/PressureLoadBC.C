//* all reserve by SuQingji
//* suqj5@mail2.sysu.edu.cn

#include "PressureLoadBC.h"

registerMooseObject("huskyApp", PressureLoadBC);

InputParameters
PressureLoadBC::validParams()
{
    InputParameters params = IntegratedBC::validParams();
    params.addRequiredParam<unsigned>("component", "compoent");
    params.addParam<Real>("value",
                          0.0,
                          "pressure load.");
    return params;
}

PressureLoadBC::PressureLoadBC(const InputParameters &parameters)
    : IntegratedBC(parameters),
      _value(getParam<Real>("value")),
      _G(getMaterialProperty<Real>("G")),
      _E(getMaterialProperty<Real>("E")),
      _lambda(getMaterialProperty<Real>("lambda")),
      _component(getParam<unsigned>("component"))
{
}

Real PressureLoadBC::computeQpResidual()
{
    Real var = 0;
    if (_component == 0)
        var = _value / _E[_qp] * _G[_qp] + _value / _E[_qp] * (_lambda[_qp] + _G[_qp]);
    // if (_component == 1)
        // var = _value / _E[_qp] * (_lambda[_qp] + _G[_qp]);

    return -_test[_i][_qp] * var;
}