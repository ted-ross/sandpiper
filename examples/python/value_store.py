#!/usr/bin/env python
#
# Licensed to the Apache Software Foundation (ASF) under one
# or more contributor license agreements.  See the NOTICE file
# distributed with this work for additional information
# regarding copyright ownership.  The ASF licenses this file
# to you under the Apache License, Version 2.0 (the
# "License"); you may not use this file except in compliance
# with the License.  You may obtain a copy of the License at
#
#   http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing,
# software distributed under the License is distributed on an
# "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
# KIND, either express or implied.  See the License for the
# specific language governing permissions and limitations
# under the License.
#

from proton.handlers import MessagingHandler
from proton.reactor import Container
from sandpiper.request_response import RequestServer, Request

class ValueStore(MessagingHandler):
    def __init__(self, bus_address, service_address):
        super(ValueStore, self).__init__()
        self.bus_address     = bus_address
        self.service_address = service_address
        self.stored_value    = 0

    def on_start(self, event):
        self.container = event.container
        self.conn = self.container.connect(self.bus_address)
        self.server = RequestServer(self.container, self.conn, self.service_address)

    def on_request(self, event):
        try:
            props = event.request.properties
            if not props:
                raise Exception("Request has no properties")
            opcode = props['opcode']
            if opcode == "SET":
                self.stored_value = props['value']
            elif opcode == "GET":
                props['value'] = self.stored_value
            else:
                raise Exception("Unknown opcode: %s" % opcode)
            self.server.reply(event.request, props)
        except Exception, e:
            self.server.fail(event.request, "%r" % e)


Container(ValueStore("127.0.0.1:5672", "counterValue")).run()

