#include "BlueprintAssistTypes.h"

#include "EdGraph/EdGraph.h"

void FBAGraphPinHandle::SetPin(UEdGraphPin* Pin)
{
	if (!FBAUtils::IsValidPin(Pin))
	{
		Invalidate();
	}
	else if (UEdGraphNode* Node = Pin->GetOwningNodeUnchecked())
	{
		Graph = Node->GetGraph();
		NodeGuid = Node->NodeGuid;
		PinId = Pin->PinId;
		PinType = Pin->PinType;
		PinName = Pin->PinName;
	}
}

UEdGraphPin* FBAGraphPinHandle::GetPin()
{
	if (!IsValid())
	{
		return nullptr;
	}

	for (auto Node : Graph->Nodes)
	{
		if (Node->NodeGuid == NodeGuid)
		{
			for (UEdGraphPin* Pin : Node->Pins)
			{
				if (Pin->PinId == PinId)
				{
					return Pin;
				}
			}

			// guid failed, find using PinType & PinName
			for (UEdGraphPin* Pin : Node->Pins)
			{
				if (Pin->PinType == PinType && Pin->PinName == PinName)
				{
					// side effect: also update the latest PinId
					PinId = Pin->PinId;

					return Pin;
				}
			}

			return nullptr;
		}
	}

	return nullptr;
}

void FBANodePinHandle::SetPin(UEdGraphPin* Pin)
{
	if (Pin)
	{
		PinId = Pin->PinId;
		Node = Pin->GetOwningNode();
		PinType = Pin->PinType;
		PinName = Pin->PinName;
	}
	else
	{
		PinId.Invalidate();
		Node = nullptr;
		PinType.ResetToDefaults();
		PinName = NAME_None;
	}
}

UEdGraphPin* FBANodePinHandle::GetPin()
{
	if (!IsValid())
	{
		return nullptr;
	}

	for (UEdGraphPin* Pin : Node->Pins)
	{
		if (Pin->PinId == PinId)
		{
			return Pin;
		}
	}

	// guid failed, find using PinType & PinName
	for (UEdGraphPin* Pin : Node->Pins)
	{
		if (Pin->PinType == PinType && Pin->PinName == PinName)
		{
			// side effect: also update the latest PinId
			PinId = Pin->PinId;

			return Pin;
		}
	}

	return nullptr;
}

void FBANodeMovementTransaction::Begin(const TSet<UEdGraphNode*>& Nodes)
{
	if (OriginalNodePositions.Num() > 0)
	{
		return;
	}

	for (UEdGraphNode* Node : Nodes)
	{
		OriginalNodePositions.Add(Node, FVector2D(Node->NodePosX, Node->NodePosY));
	}
}

void FBANodeMovementTransaction::End(const FText& SessionName)
{
	if (OriginalNodePositions.Num() == 0)
	{
		return;
	}

	TMap<UEdGraphNode*, FVector2D> NewLocations;

	FScopedTransaction Transaction(SessionName);

	// temporarily move all nodes back to their original location before we call modify
	for (const auto& OriginalNodePosition : OriginalNodePositions)
	{
		const TWeakObjectPtr<UEdGraphNode>& NodePtr = OriginalNodePosition.Key;
		if (NodePtr.IsValid())
		{
			NewLocations.Add(NodePtr.Get(), FVector2D(NodePtr->NodePosX, NodePtr->NodePosY));
			NodePtr->NodePosX = OriginalNodePosition.Value.X;
			NodePtr->NodePosY = OriginalNodePosition.Value.Y;
			NodePtr->Modify();
		}
	}

	// move all nodes back to their new location
	for (const auto& NewLocation : NewLocations)
	{
		NewLocation.Key->NodePosX = NewLocation.Value.X;
		NewLocation.Key->NodePosY = NewLocation.Value.Y;
	}

	OriginalNodePositions.Empty();
}
