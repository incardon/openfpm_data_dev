
/*
 * MemBalanced.hpp
 *
 *  Created on: Mar 22, 2015
 *  Last modified: June 25, 2015
 *      Authors: Pietro Incardona, Yaroslav Zaluzhnyi
 */

#ifndef CELLLISTBAL_HPP_
#define CELLLISTBAL_HPP_

#include "CellList.hpp"
#include "Space/SpaceBox.hpp"
#include "util/mathutil.hpp"
#include "CellNNIterator.hpp"
#include "Space/Shape/HyperCube.hpp"

/*! \brief Class for BALANCED cell list implementation
 *
 * This class implement the BALANCED cell list is fast (not best)
 * The memory allocation is small (not best).
 * The memory allocation is (in byte) Size = M*16 + N*sizeof(ele)
 *
 * Where
 *
 * N = total number of elements
 * M = number of cells
 * sizeof(ele) = the size of the element the cell list is storing, example if
 *               the cell list store the particle id (64bit) is 8 byte
 *
 * \warning Do not use for extremely fine cell list (M big)
 *
 * \tparam dim Dimensionality of the space
 * \tparam T type of the space float, double, complex
 *
 */
class Mem_bal
{
	//! vector that store the information
	typedef openfpm::vector<size_t> base;

	//! each cell has a pointer to a dynamic structure
	// that store the elements in the cell
	openfpm::vector<base> cl_base;

	//! Invalid element
	size_t invalid;

public:

	/*! \brief Initialize all to zero
	 *
	 * \param slot number of slot (unused)
	 * \param tot_n_cell total number of cells
	 *
	 */
	inline void init_to_zero(size_t slot, size_t tot_n_cell)
	{
		//resize the vector to needed number of cells

		cl_base.resize(tot_n_cell);
	}

	/*! \brief Copy mem balanced
	 *
	 * \param cell memory to copy
	 *
	 * \return itself
	 *
	 */
	inline Mem_bal & operator=(const Mem_bal & cell)
	{
		cl_base = cell.cl_base;

		return *this;
	}

	/*! \brief Add an element to the cell
	 *
	 * \param cell_id id of the cell
	 * \param ele element to add
	 *
	 */
	inline void addCell(size_t cell_id, typename base::value_type ele)
	{
		//add another neighbor element

		cl_base.get(cell_id).add(ele);
	}

	/*! \brief Add an element to the cell
	 *
	 * \param cell_id id of the cell
	 * \param ele element to add
	 *
	 */
	inline void add(size_t cell_id, typename base::value_type ele)
	{
		this->addCell(cell_id,ele);
	}

	/*! \brief Remove an element from the cell
	 *
	 * \param cell_id id of the cell
	 * \param ele element to remove
	 *
	 */
	inline void remove(size_t cell, size_t ele)
	{
		cl_base.get(cell).remove(ele);
	}

	/*! \brief Get the number of elements in the cell
	 *
	 * \param cell_id id of the cell
	 *
	 * \return the number of elements in the cell
	 *
	 */
	inline size_t getNelements(const size_t cell_id) const
	{
		return cl_base.get(cell_id).size();
	}

	/*! \brief Return an element from the cell
	 *
	 * \param cell id of the cell
	 * \param ele element id
	 *
	 * \return reference to the element
	 *
	 */
	inline auto get(size_t cell, size_t ele) -> decltype(cl_base.get(0).get(0)) &
	{
		return cl_base.get(cell).get(ele);
	}

	/*! \brief Return an element from the cell
	 *
	 * \param cell id of the cell
	 * \param ele element id
	 *
	 * \return reference to the element
	 *
	 */
	inline auto get(size_t cell, size_t ele) const -> decltype(cl_base.get(0).get(0)) &
	{
		return cl_base.get(cell).get(ele);
	}

	/*! \brief Swap two Mem_bal
	 *
	 * \param cl element to swap with
	 *
	 */
	inline void swap(Mem_bal & cl)
	{
		cl_base.swap(cl.cl_base);
	}

	/*! \brief Swap two Mem_bal
	 *
	 * \param cl element to swap with
	 *
	 */
	inline void swap(Mem_bal && cell)
	{
		cl_base.swap(cell.cl_base);
	}

	/*! \brief Reset the object
	 *
	 *
	 */
	inline void clear()
	{
		for (size_t i = 0 ; i < cl_base.size() ; i++)
			cl_base.get(i).clear();
	}

	inline const size_t & getStartId(size_t part_id) const
	{
		if (cl_base.get(part_id).size() == 0)
			return invalid;

		return cl_base.get(part_id).get(0);
	}

	inline const size_t & getStopId(size_t part_id) const
	{
		if (cl_base.get(part_id).size() == 0)
			return invalid;

		return *(&cl_base.get(part_id).last() + 1);
	}

	inline const size_t & get_lin(const size_t * part_id) const
	{
		return *part_id;
	}

public:

	inline Mem_bal(size_t slot)
	:invalid(0)
	{}

	inline void set_slot(size_t slot)
	{}

};


#endif /* CELLLISTBAL_HPP_ */