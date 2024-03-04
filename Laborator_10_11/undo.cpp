#include "undo.h"

void UndoAdauga::doUndo() {
    repo.deleteRepo(disciplinaAdaugata.getDenumire());
}

void UndoSterge::doUndo() {
    repo.addRepo(disciplinaStearsa);
}

void UndoModifica::doUndo() {
    repo.updateRepo(disciplinaVeche.getDenumire(), disciplinaVeche);
}
