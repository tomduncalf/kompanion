/**
 * A Typescript implementation of JUCE's ValueTreeSynchroniser class, to
 * allow our JS app to receive ValueTree state updates. The implementation
 * is read-only, i.e. it can only receive updates, not send them.
 */

import { ValueTree } from "./ValueTree";

enum ChangeType {
  propertyChanged = 1,
  fullSync = 2,
  childAdded = 3,
  childRemoved = 4,
  childMoved = 5,
  propertyRemoved = 6,
}

export const applyChange = (valueTree: ValueTree, input: string) => {
  let readPosition = 0;

  const type: ChangeType = Number(input[readPosition]);

  if (type === ChangeType.fullSync) {
    valueTree.readFromString(input);
    return;
  }
};
