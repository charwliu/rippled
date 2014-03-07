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

#ifndef RIPPLE_SERIALIZEDLEDGER_H
#define RIPPLE_SERIALIZEDLEDGER_H

// VFALCO NOTE
//
//      This looks like a central class for Ripple. Almost everything that
//      does anything of interest deals with SLE objects. Any documentation
//      effort should start with a complete description of this object and
//      all of its operations.
//
//      It is derived from STObject so it inherits a lot of behavior from that.
//
// VFALCO TODO Rename the source file to match the class
//
// VFALCO TODO Can we rename this class to something shorter and more concise?
//
//             Can we just call this LedgerEntry?
//
class SerializedLedgerEntry
    : public STObject
    , public CountedObject <SerializedLedgerEntry>
{
public:
    static char const* getCountedObjectName () { return "SerializedLedgerEntry"; }

    typedef boost::shared_ptr<SerializedLedgerEntry>        pointer;
    typedef const boost::shared_ptr<SerializedLedgerEntry>& ref;

public:
    SerializedLedgerEntry (const Serializer & s, uint256 const & index);
    SerializedLedgerEntry (SerializerIterator & sit, uint256 const & index);
    SerializedLedgerEntry (LedgerEntryType type, uint256 const & index);

    SerializedTypeID getSType () const
    {
        return STI_LEDGERENTRY;
    }
    std::string getFullText () const;
    std::string getText () const;
    Json::Value getJson (int options) const;

    uint256 const& getIndex () const
    {
        return mIndex;
    }
    void setIndex (uint256 const & i)
    {
        mIndex = i;
    }

    void setImmutable ()
    {
        mMutable = false;
    }
    bool isMutable ()
    {
        return mMutable;
    }
    SerializedLedgerEntry::pointer getMutable () const;

    LedgerEntryType getType () const
    {
        return mType;
    }
    beast::uint16 getVersion () const
    {
        return getFieldU16 (sfLedgerEntryType);
    }
    LedgerFormats::Item const* getFormat ()
    {
        return mFormat;
    }

    bool isThreadedType (); // is this a ledger entry that can be threaded
    bool isThreaded ();     // is this ledger entry actually threaded
    bool hasOneOwner ();    // This node has one other node that owns it (like nickname)
    bool hasTwoOwners ();   // This node has two nodes that own it (like ripple balance)
    RippleAddress getOwner ();
    RippleAddress getFirstOwner ();
    RippleAddress getSecondOwner ();
    uint256 getThreadedTransaction ();
    beast::uint32 getThreadedLedger ();
    bool thread (uint256 const & txID, beast::uint32 ledgerSeq, uint256 & prevTxID,
                 beast::uint32 & prevLedgerID);
    std::vector<uint256> getOwners ();  // nodes notified if this node is deleted

private:
    SerializedLedgerEntry* duplicate () const
    {
        return new SerializedLedgerEntry (*this);
    }

private:
    uint256                     mIndex;
    LedgerEntryType             mType;
    LedgerFormats::Item const*  mFormat;
    bool                        mMutable;
};

typedef SerializedLedgerEntry SLE;

#endif
// vim:ts=4
