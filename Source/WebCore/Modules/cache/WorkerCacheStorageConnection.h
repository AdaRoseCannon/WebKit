
/*
 * Copyright (C) 2017 Apple Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE INC. AND ITS CONTRIBUTORS ``AS IS''
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL APPLE INC. OR ITS CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 */

#pragma once

#include "CacheStorageConnection.h"

#include "ResourceRequest.h"

namespace WebCore {

class WorkerGlobalScope;
class WorkerLoaderProxy;

class WorkerCacheStorageConnection final : public CacheStorageConnection {
public:
    static Ref<WorkerCacheStorageConnection> create(WorkerGlobalScope& scope) { return adoptRef(*new WorkerCacheStorageConnection(scope)); }
    ~WorkerCacheStorageConnection();

private:
    explicit WorkerCacheStorageConnection(WorkerGlobalScope&);

    // WebCore::CacheStorageConnection.
    Ref<OpenPromise> open(const ClientOrigin&, const String& cacheName) final;
    Ref<RemovePromise> remove(DOMCacheIdentifier) final;
    Ref<RetrieveCachesPromise> retrieveCaches(const ClientOrigin&, uint64_t updateCounter) final;

    Ref<RetrieveRecordsPromise> retrieveRecords(DOMCacheIdentifier, RetrieveRecordsOptions&&) final;
    Ref<BatchPromise> batchDeleteOperation(DOMCacheIdentifier, const ResourceRequest&, CacheQueryOptions&&) final;
    Ref<BatchPromise> batchPutOperation(DOMCacheIdentifier, Vector<DOMCacheEngine::CrossThreadRecord>&&) final;

    void reference(DOMCacheIdentifier) final;
    void dereference(DOMCacheIdentifier) final;
    void lockStorage(const ClientOrigin&) final;
    void unlockStorage(const ClientOrigin&) final;

    WorkerGlobalScope& m_scope;
    Ref<CacheStorageConnection> m_mainThreadConnection;
};

} // namespace WebCore
