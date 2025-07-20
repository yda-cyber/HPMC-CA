"""Type-based harmonic potential."""

import hoomd
from hoomd.data.parameterdicts import TypeParameterDict
from hoomd.data.typeparam import TypeParameter
from .external import External


@hoomd.logging.modify_namespace(("hpmc", "external", "TypeHarmonic"))
class TypeHarmonic(External):
    """Type-based harmonic potential.

    Args:
        k_translational (`dict`): Harmonic spring constants (`kx`, `ky`, `kz`)
            for each particle type. Example:
            `{'A': (1.0, 1.0, 1.0), 'B': (2.0, 2.0, 2.0)}`
        reference_positions (`numpy.ndarray`): Reference positions for each
            particle, with shape (*N_particles*, 3) :math:`[\\mathrm{length}]`.

    This external field applies a harmonic spring force on particles based on
    their type and distance from their reference positions.
    """

    _cpp_class_name = "ExternalFieldTypeHarmonic"

    def __init__(self, k_translational, reference_positions):
        super().__init__()
        self.k_translational = k_translational
        self.reference_positions = reference_positions

    def _make_cpp_obj(self):
        """Create the underlying C++ object."""
        cpp_sys_def = self._simulation.state._cpp_sys_def
        cls = getattr(self._ext_module, self._cpp_class_name)
        return cls(cpp_sys_def, self.k_translational, self.reference_positions)