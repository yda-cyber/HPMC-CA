#pragma once

#include "hoomd/Compute.h"
#include "hoomd/VectorMath.h"
#include "hoomd/ParticleData.h"
#include "ExternalPotential.h"

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace hoomd
{
namespace hpmc
{

class ExternalFieldTypeHarmonic  : public ExternalPotential
{
public:
    //! Constructor
    ExternalFieldTypeHarmonic(std::shared_ptr<SystemDefinition> sysdef,
                              pybind11::dict k_translational,
                              pybind11::array_t<double> reference_positions)
        : ExternalPotential(sysdef), m_sysdef(sysdef), m_pdata(sysdef->getParticleData())
    	{
    	std::cout << "Constructing TypeHarmonic" << std::endl;
    	std::cout << "Number of particle types: " << sysdef->getParticleData()->getNTypes() << std::endl;
    	for (auto &item : k_translational)
    	{
        	std::string type_name = item.first.cast<std::string>();
        	std::cout << "Type: " << type_name << std::endl;
    	}
    	std::cout << "Reference positions shape: " << reference_positions.shape(0)
              	<< " x " << reference_positions.shape(1) << std::endl;
        // Parse spring constants (kx, ky, kz) for each type
        const auto &type_mapping = m_pdata->getTypeMapping();
        for (auto &elem : k_translational)
        {
            std::string type_name = elem.first.cast<std::string>();
            unsigned int type_id = m_pdata->getTypeByName(type_name);

            auto k_tuple = elem.second.cast<pybind11::tuple>();
            if (k_tuple.size() != 3)
            {
                throw std::runtime_error("k_translational must be a tuple of size 3 (kx, ky, kz)."
                );
            }
            m_k_translational[type_id] = vec3<Scalar>(k_tuple[0].cast<Scalar>(),
                                                      k_tuple[1].cast<Scalar>(),
                                                      k_tuple[2].cast<Scalar>());
        }

        // Parse reference positions
        if (reference_positions.ndim() != 2 || reference_positions.shape(1) != 3)
        {
            throw std::runtime_error(
                "reference_positions must be a (N_particles, 3) array.");
        }

        size_t N = reference_positions.shape(0);
        const double *data = static_cast<const double *>(reference_positions.data());
        for (size_t i = 0; i < N; ++i)
        {
            m_reference_positions.push_back(vec3<Scalar>(data[3 * i], data[3 * i + 1], data[3 * i + 2]));
        }
    }

    //! Evaluate the lattice constraint energy of a single particle.
    virtual LongReal particleEnergyImplementation(uint64_t timestep,
                                              	unsigned int tag_i,
                                              	unsigned int type_i,
                                              	const vec3<LongReal>& r_i,
                                              	const quat<LongReal>& q_i,
                                              	LongReal charge_i,
                                              	Trial trial = Trial::None) override
    {
    	// Call computeEnergy with appropriate arguments
    	return computeEnergy(type_i, vec3<Scalar>(r_i.x, r_i.y, r_i.z), tag_i);
    }


    //! Compute the energy of a single particle
    Scalar computeEnergy(unsigned int type_id, 
			const vec3<Scalar> &position, unsigned int particle_id)
    {
        vec3<Scalar> dr = position - m_reference_positions[particle_id];
        vec3<Scalar> k = m_k_translational[type_id];
        return Scalar(0.5) * (k.x * dr.x * dr.x + k.y * dr.y * dr.y + k.z * dr.z * dr.z);
    }

private:
    std::shared_ptr<SystemDefinition> m_sysdef;
    std::shared_ptr<ParticleData> m_pdata;
    std::vector<vec3<Scalar>> m_reference_positions; // Reference positions
    std::unordered_map<unsigned int, vec3<Scalar>> m_k_translational; // Spring constants per type
};

namespace detail
{
void export_ExternalFieldTypeHarmonic(pybind11::module &m)
{
    pybind11::class_<ExternalFieldTypeHarmonic, ExternalPotential, std::shared_ptr<ExternalFieldTypeHarmonic>>(
        m, "ExternalFieldTypeHarmonic")
        .def(pybind11::init<std::shared_ptr<SystemDefinition>, pybind11::dict, pybind11::array_t<double>>())
        .def("computeEnergy", &ExternalFieldTypeHarmonic::computeEnergy);
}
} // namespace detail

} // namespace hpmc
} // namespace hoomd
