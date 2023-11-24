//* all reserve by SuQingji
//* suqj5@mail2.sysu.edu.cn

#include "ComputeOthers.h"

registerMooseObject("huskyApp", ComputeOthers);

InputParameters
ComputeOthers::validParams()
{
    InputParameters params = Material::validParams();
    params.addCoupledVar(
        "u",
        "The gradient of this variable will be used to compute a velocity vector property.");
    params.addCoupledVar(
        "v",
        "The gradient of this variable will be used to compute a velocity vector property.");

    return params;
}

ComputeOthers::ComputeOthers(const InputParameters &parameters)
    : Material(parameters),
      _epsilon_x(declareProperty<Real>("epsilon_x")),
      _epsilon_y(declareProperty<Real>("epsilon_y")),
      _epsilon_xy(declareProperty<Real>("epsilon_xy")),
      _sigma_x(declareProperty<Real>("sigma_x")),
      _sigma_y(declareProperty<Real>("sigma_y")),
      _sigma_xy(declareProperty<Real>("sigma_xy")),
      _Mises(declareProperty<Real>("Mises")),
      _G(declareProperty<Real>("G")),
      _lambda(declareProperty<Real>("lambda")),
      _E(declareProperty<Real>("E")),
      _mu(declareProperty<Real>("mu")),

      _u(coupledValue("u")),
      _v(coupledValue("v")),
      _grad_u(coupledGradient("u")),
      _grad_v(coupledGradient("v"))
{
}

void ComputeOthers::computeQpProperties()
{
    _E[_qp] = 210000;
    _mu[_qp] = 0.3;

    _G[_qp] = _E[_qp] / 2 / (1 + _mu[_qp]);
    _lambda[_qp] = _E[_qp] * _mu[_qp] / (1 - 2 * _mu[_qp]) / (1 + _mu[_qp]);

    _epsilon_x[_qp] = _grad_u[_qp](0);
    _epsilon_y[_qp] = _grad_v[_qp](1);
    _epsilon_xy[_qp] = _grad_u[_qp](1) + _grad_v[_qp](0);

    _sigma_x[_qp] = 2 * _G[_qp] * _epsilon_x[_qp] + _lambda[_qp] * (_epsilon_x[_qp] + _epsilon_y[_qp]);
    _sigma_y[_qp] = 2 * _G[_qp] * _epsilon_y[_qp] + _lambda[_qp] * (_epsilon_x[_qp] + _epsilon_y[_qp]);
    _sigma_xy[_qp] = _G[_qp] * _epsilon_xy[_qp];

    _Mises[_qp] = std::sqrt(_sigma_x[_qp] * _sigma_x[_qp] -
                            _sigma_x[_qp] * _sigma_y[_qp] +
                            _sigma_y[_qp] * _sigma_y[_qp] +
                            3 * _sigma_xy[_qp] * _sigma_xy[_qp]);
}
