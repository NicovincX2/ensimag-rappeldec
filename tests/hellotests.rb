#!/usr/bin/ruby
# -*- coding: utf-8 -*-

# Copyright (C) 2016 Gregory Mounie
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or (at
# your option) any later version.
 
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# General Public License for more details.
 
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

require "test/unit"
require "expect"
require "pty"

class TestHello < Test::Unit::TestCase
  test_order=:defined

  def setup
    @pty_read, @pty_write, @pty_pid = PTY.spawn("../build/hello")
  end

  def teardown
    # ne rien faire
  end

  def test_hello
    a = @pty_read.expect(/∀p *∈ *world *, *hello *p/m, 1) # attendre 1 seconde pour le hello world utf8
    assert_not_nil(a, "Chaîne de caractère différente  de '∀p ∈ world , hello p' ou absente")
  end

  def test_all
    test_hello
  end
end
