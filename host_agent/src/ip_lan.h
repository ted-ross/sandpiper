#ifndef HOST_AGENT_IP_LAN_H
#define HOST_AGENT_IP_LAN_H 1
/*
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */

#include <qpid/dispatch/error.h>

typedef struct sp_interface_t;

/**
 * Create a new network interface
 *
 * @param if_name The interface name
 * @param domain The domain of the sandpiper deployment (or 0 if not used)
 * @param vlan The name of the virtual lan
 * @return A pointer to the new sp_interface object or 0 if there was an error.
 */
sp_interface_t *sp_interface(const char *if_name, const char *domain, const char *vlan);

/**
 * Free a network interface object
 *
 * @param i Pointer to an sp_interface object created by sp_interface()
 */
void sp_interface_free(sp_interface_t *i);

/**
 * Set an inbound tag for the interface.
 *
 * @param i Pointer to an sp_interface object created by sp_interface()
 * @param tag A tag to be used on inbound (to the network interface) packets or 0 to
 *        disable inbound tagging.
 */
void sp_interface_set_inbound_tag(sp_interface_t *i, const char *tag);

/**
 * Set an outbound tag for the interface.
 *
 * @param i Pointer to an sp_interface object created by sp_interface()
 * @param tag A tag to be used on outbound (from the network interface) packets or 0 to
 *        disable outbound tagging.
 */
void sp_interface_set_outbound_tag(sp_interface_t *i, const char *tag);

/**
 * Add an IP(v4) subnet address to the interface
 *
 * @param i Pointer to an sp_interface object created by sp_interface()
 * @param addr Base IP address of the CIDR subnet
 * @param cidr_net The number of address bits in the host part of the address
 *        (class A = 8, class B = 16, class C = 24, etc.)
 * @return Error code
 */
qd_error_t sp_interface_add_ip(sp_interface_t *i, uint32_t addr, uint32_t cidr_net);

/**
 * Add an IP(v6) subnet address to the interface
 *
 * @param i Pointer to an sp_interface object created by sp_interface()
 * @param addr Base IP address of the CIDR subnet
 * @param cidr_net The number of address bits in the host part of the address
 * @return Error code
 */
qd_error_t sp_interface_add_ip6(sp_interface_t *i, uint32_t *addr, uint32_t cidr_net);

/**
 * Add an IP(v6) broadcast address to the interface
 *
 * @param i Pointer to an sp_interface object created by sp_interface()
 * @param addr Broadcast address
 * @return Error code
 */
qd_error_t sp_interface_add_ip6_bcast(sp_interface_t *i, uint32_t *addr);

/**
 * Add an IP(v6) anycast address to the interface
 *
 * @param i Pointer to an sp_interface object created by sp_interface()
 * @param addr Anycast address
 * @return Error code
 */
qd_error_t sp_interface_add_ip6_anycast(sp_interface_t *i, uint32_t *addr);

/**
 * Create the interface in the specified network namespace
 *
 * @param i Pointer to an sp_interface object created by sp_interface()
 * @param ns_pid String representation of the target container's pid
 * @return Error code
 */
qd_error_t sp_interface_open_in_netns(sp_interface_t *i, const char *ns_pid);

/**
 * Given the octets from an IP header, determine the AMQP address for encapsulation
 *
 * @param i Pointer to an sp_interface object created by sp_interface()
 * @param buffer Contiguous buffer of octets starting with the IP header
 * @param addr Buffer into which to place the extracted AMQP address
 * @param len Length of the output buffer (addr)
 */
void sp_interface_extract_addr(sp_interface_t *i, const unsigned char *buffer, char *addr, int len);

#endif
