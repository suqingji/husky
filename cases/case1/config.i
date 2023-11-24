[Mesh]
  [grid]
    type = FileMeshGenerator
    file = grid.exo
  []
  uniform_refine = 3
[]

[Variables]
  [u]
    order = FIRST
    family = LAGRANGE
  []
  [v]
    order = FIRST
    family = LAGRANGE
  []
[]

[Kernels]
  [displx]
    type = SolidElasticMechanics
    variable = u
    component = 0
  []
  [disply]
    type = SolidElasticMechanics
    variable = v
    component = 1
  []
[]

[BCs]
  [left]
    type = DirichletBC
    variable = u
    boundary = "left"
    value = 0
  []

  [bottom]
    type = DirichletBC
    variable = v
    boundary = "bottom"
    value = 0
  []

  [right_u]
    type = PressureLoadBC
    variable = u
    boundary = "right"
    value = 100
    component = 0
  []
  [right_v]
    type = PressureLoadBC
    variable = v
    boundary = "right"
    value = 100
    component = 1
  []
[]

[Executioner]
  type = Steady
  solve_type = 'NEWTON'
  petsc_options_iname = '-pc_type'
  petsc_options_value = 'lu'
[]

[Outputs]
  exodus = true
  vtk = true
[]

[AuxVariables]
  [Mises]
    #  order = CONSTANT
    order = FIRST
    family = MONOMIAL
  []
[]
[AuxKernels]
  [copy_bar]
    type = MaterialRealAux
    property = Mises
    variable = Mises
  []
[]
[Materials]
  [thermal_cond]
    type = ComputeOthers
    u = u
    v = v
  []
[]
