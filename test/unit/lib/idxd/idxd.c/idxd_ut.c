/*-
 *   BSD LICENSE
 *
 *   Copyright (c) Intel Corporation.
 *   All rights reserved.
 *
 *   Redistribution and use in source and binary forms, with or without
 *   modification, are permitted provided that the following conditions
 *   are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in
 *       the documentation and/or other materials provided with the
 *       distribution.
 *     * Neither the name of Intel Corporation nor the names of its
 *       contributors may be used to endorse or promote products derived
 *       from this software without specific prior written permission.
 *
 *   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *   "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *   A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *   OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *   SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *   LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *   DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *   THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *   (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *   OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "spdk_cunit.h"
#include "spdk_internal/mock.h"
#include "spdk_internal/idxd.h"
#include "common/lib/test_env.c"

#include "idxd/idxd.h"
#include "idxd/idxd.c"

static void
user_idxd_set_config(struct device_config *dev_cfg, uint32_t config_num)
{
}

static struct spdk_idxd_impl g_user_idxd_impl = {
	.name		= "user",
	.set_config	= user_idxd_set_config,
};

static int
test_spdk_idxd_set_config(void)
{

	g_dev_cfg = NULL;
	spdk_idxd_set_config(0);
	SPDK_CU_ASSERT_FATAL(g_dev_cfg != NULL);
	CU_ASSERT(memcmp(&g_dev_cfg0, g_dev_cfg, sizeof(struct device_config)) == 0);

	return 0;
}

static int
test_setup(void)
{
	idxd_impl_register(&g_user_idxd_impl);

	g_dev_cfg = &g_dev_cfg0;
	return 0;
}

int main(int argc, char **argv)
{
	CU_pSuite	suite = NULL;
	unsigned int	num_failures;

	CU_set_error_action(CUEA_ABORT);
	CU_initialize_registry();

	suite = CU_add_suite("idxd", test_setup, NULL);

	CU_ADD_TEST(suite, test_spdk_idxd_set_config);

	CU_basic_set_mode(CU_BRM_VERBOSE);
	CU_basic_run_tests();
	num_failures = CU_get_number_of_failures();
	CU_cleanup_registry();
	return num_failures;
}
