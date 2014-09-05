/*
    Authors:
        Pavel Březina <pbrezina@redhat.com>

    Copyright (C) 2014 Red Hat

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef RESPONDER_CACHE_H_
#define RESPONDER_CACHE_H_

#include <talloc.h>
#include <tevent.h>
#include "db/sysdb.h"
#include "responder/common/responder.h"
#include "responder/common/negcache.h"

/**
 * Currently only SSS_DP_USER and SSS_DP_INITGROUPS are supported.
 *
 * @todo support other request types
 */
struct tevent_req *cache_req_send(TALLOC_CTX *mem_ctx,
                                  struct tevent_context *ev,
                                  struct resp_ctx *rctx,
                                  struct sss_nc_ctx *ncache,
                                  int neg_timeout,
                                  int cache_refresh_percent,
                                  enum sss_dp_acct_type dp_type,
                                  const char *domain,
                                  const char *name);

errno_t cache_req_recv(TALLOC_CTX *mem_ctx,
                       struct tevent_req *req,
                       struct ldb_result **_result,
                       struct sss_domain_info **_domain);

#define cache_req_user_by_name_send(mem_ctx, ev, rctx, ncache, neg_timeout, \
                                    cache_refresh_percent, domain, name) \
    cache_req_send(mem_ctx, ev, rctx, ncache, neg_timeout, \
                   cache_refresh_percent, SSS_DP_USER, domain, name)

#define cache_req_user_by_name_recv(mem_ctx, req, _result, _domain) \
    cache_req_recv(mem_ctx, req, _result, _domain)

#define cache_req_initgr_by_name_send(mem_ctx, ev, rctx, ncache, neg_timeout, \
                                      cache_refresh_percent, domain, name) \
    cache_req_send(mem_ctx, ev, rctx, ncache, neg_timeout, \
                   cache_refresh_percent, SSS_DP_INITGROUPS, domain, name)

#define cache_req_initgr_by_name_recv(mem_ctx, req, _result, _domain) \
    cache_req_recv(mem_ctx, req, _result, _domain)

#endif /* RESPONDER_CACHE_H_ */
