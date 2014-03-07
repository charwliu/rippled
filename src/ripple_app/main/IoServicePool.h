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

#ifndef RIPPLE_APP_IOSERVICEPOOL_H_INCLUDED
#define RIPPLE_APP_IOSERVICEPOOL_H_INCLUDED

/** An io_service with an associated group of threads. */
class IoServicePool : public beast::Stoppable
{
public:
    IoServicePool (Stoppable& parent, beast::String const& name, int numberOfThreads);
    ~IoServicePool ();

    boost::asio::io_service& getService ();
    operator boost::asio::io_service& ();

    void onStart ();
    void onStop ();
    void onChildrenStopped ();

private:
    class ServiceThread;

    void onThreadExit();

    beast::String m_name;
    boost::asio::io_service m_service;
    boost::optional <boost::asio::io_service::work> m_work;
    beast::OwnedArray <ServiceThread> m_threads;
    int m_threadsDesired;
    beast::Atomic <int> m_threadsRunning;
};

#endif
