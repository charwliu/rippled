//------------------------------------------------------------------------------
/*
    This file is part of rippled: https://github.com/ripple/rippled
    Copyright (c) 2012, 2013 Ripple Labs Inc.

    Permission to use, copy, modify, and/or distribute this software for any
    purpose  with  or without fee is hereby granted, provided that the above
    copyright notice and this permission notice appear in all copies.

    THE  SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
    WITH  REGARD  TO  THIS  SOFTWARE  INCLUDING  ALL  IMPLIED  WARRANTIES  OF
    MERCHANTABILITY  AND  FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
    ANY  SPECIAL ,  DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
    WHATSOEVER  RESULTING  FROM  LOSS  OF USE, DATA OR PROFITS, WHETHER IN AN
    ACTION  OF  CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
    OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*/
//==============================================================================

#ifndef RIPPLE_PROTOCOL_H
#define RIPPLE_PROTOCOL_H

/** Protocol specific constants, types, and data.

    This information is part of the Ripple protocol. Specifically,
    it is required for peers to be able to communicate with each other.

    @note Changing these will create a hard fork.

    @ingroup protocol
    @defgroup protocol
*/
struct Protocol
{
    /** Smallest legal byte size of a transaction.
    */
    static int const txMinSizeBytes = 32;

    /** Largest legal byte size of a transaction.
    */
    static int const txMaxSizeBytes = 1024 * 1024; // 1048576
};

/** A ledger index.
*/
// VFALCO TODO pick one. I like Index since its not an abbreviation
typedef beast::uint32 LedgerIndex;
// VFALCO NOTE "LedgerSeq" appears in some SQL statement text
typedef beast::uint32 LedgerSeq;

/** A transaction identifier.
*/
// VFALCO TODO maybe rename to TxHash
typedef uint256 TxID;

/** A transaction index.
*/
typedef beast::uint32 TxSeq; // VFALCO NOTE Should read TxIndex or TxNum

/** An account hash.

    The hash is used to uniquely identify the account.
*/
//typedef uint160 AccountHash;
//typedef uint260 ValidatorID;

#endif
