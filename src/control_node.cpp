/* Copyright (C) 2015-2018 Michele Colledanchise -  All Rights Reserved
 * Copyright (C) 2018 Davide Faconti -  All Rights Reserved
*
*   Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"),
*   to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
*   and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
*   The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
*
*   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
*   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
*   WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include "behavior_tree_core/control_node.h"

BT::ControlNode::ControlNode(std::string name) : TreeNode::TreeNode(name)
{
    // TODO(...) In case it is desired to set to idle remove the ReturnStatus
    // type in order to set the member variable
    // ReturnStatus child_i_status_ = BT::IDLE;  // commented out as unused
}

void BT::ControlNode::addChild(TreeNode* child)
{
    // Checking if the child is not already present
    for (auto node : children_nodes_)
    {
        if (node == child)
        {
            throw BehaviorTreeException("'" + child->name() + "' is already a '" + name() + "' child.");
        }
    }

    children_nodes_.push_back(child);
}

unsigned int BT::ControlNode::childrenCount() const
{
    return children_nodes_.size();
}

void BT::ControlNode::halt()
{
    DEBUG_STDOUT("HALTING: " << name());
    haltChildren(0);
    setStatus(BT::HALTED);
}

const std::vector<BT::TreeNode*>& BT::ControlNode::children() const
{
    return children_nodes_;
}

void BT::ControlNode::haltChildren(int i)
{
    for (unsigned int j = i; j < children_nodes_.size(); j++)
    {
        if (children_nodes_[j]->status() == BT::RUNNING)
        {
            DEBUG_STDOUT("SENDING HALT TO CHILD " << children_nodes_[j]->name());
            children_nodes_[j]->halt();
        }
        else
        {
            DEBUG_STDOUT("NO NEED TO HALT " << children_nodes_[j]->name() << "STATUS" << children_nodes_[j]->status());
        }
    }
}
