#ifndef BITFIELD_H
#define BITFIELD_H

#include <unistd.h>
#include <stdbool.h>

typedef struct bitfield_s {
    unsigned char * mask;         /**< A buffer that stores a bitfield */
    size_t          size_in_bits; /**< Size of the layer and its sublayers */
} bitfield_t;

//--------------------------------------------------------------------------
// Allocation
//--------------------------------------------------------------------------

/**
 * \brief Allocate a bitfield
 * \param size_in_bits Size of the layer and its sublayer
 *   For example if the bitfield is define on a probe, pass the
 *   maximum size of the probe (in bits)
 * \return The address of the bitfield (NULL if error)
 */

bitfield_t * bitfield_create(size_t size_in_bits);

/**
 * \brief Delete a bitfield from the memory
 * \param bitfield Address of this bitfield
 */

void bitfield_free(bitfield_t * bitfield);

//--------------------------------------------------------------------------
// Setter/getter 
//--------------------------------------------------------------------------

/**
 * \brief Define whether a bit belongs to a bitfield
 * \warning This function is based on the endianess of your system.
 * \param bitfield The bitfield
 * \param value Pass 0 if this bit must be set to 0, pass any 
 *     other value if this bit must be set to 1.
 * \param offset_in_bits The position of the bit in the bitfield.
 *     This value must be less than to bitfield.size_in_bits
 * \return 0 if everything is fine, another value otherwise
 */

int bitfield_set_mask_bit(
    bitfield_t * bitfield,
    int          value,
    size_t       offset_in_bits
);

/**
 * \brief Set a bloc of bits to a givent value (0 or 1) 
 * \warning This function is based on the endianess of your system.
 * \param bitfield The bitfield
 * \param value Pass 0 if each altered bit must be set to 0, pass any 
 *     other value if they must be set to 1.
 * \param offset_in_bits The position of the block of bits in the bitfield.
 *     This value must be less than bitfield.size_in_bits - 
 * \return 0 if everything is fine, another value otherwise
 */

int bitfield_set_mask_bits(
    bitfield_t * bitfield,
    int          value,
    size_t       offset_in_bits,
    size_t       num_bits
);

/**
 * \brief Retrieve the size of the internal buffer (in bits) 
 * \param bitfield The bitfield
 * \return the size in bits of the internal buffer
 */

size_t bitfield_get_size_in_bits(const bitfield_t * bitfield);

/**
 * \brief Count the number of bits set to 1 in a bitfield
 * \param bitfield The bitfield
 * \return the size in bits set to 1. 
 */

size_t  bitfield_get_num_1(const bitfield_t * bitfield);

//--------------------------------------------------------------------------
// Operators 
//--------------------------------------------------------------------------

/**
 * \brief Apply &= to each byte (tgt &= src)
 * \param tgt The left operand of &= 
 * \param src The right operand of &=
 */

void bitfield_and(bitfield_t * tgt, const bitfield_t * src);

/**
 * \brief Apply |= to each byte (tgt |= src)
 * \param tgt The left operand of |= 
 * \param src The right operand of |=
 */

void bitfield_or(bitfield_t * tgt, const bitfield_t * src);

/**
 * \brief Apply ~ to each byte (tgt ~= tgt)
 * \param tgt The bitfield we modify 
 */

void bitfield_not(bitfield_t * tgt);

#endif

