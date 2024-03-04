#pragma once
#include "domain.h"
#include "repositoryFile.h"

class ActiuneUndo {
public:
    virtual void doUndo() = 0;
    virtual ~ActiuneUndo() = default;
};

class UndoAdauga: public ActiuneUndo {
    Disciplina disciplinaAdaugata;
    Repo &repo;
public:
    UndoAdauga(Repo& repo, const Disciplina& d): repo { repo }, disciplinaAdaugata { d }{}
    void doUndo() override;
};

class UndoSterge: public ActiuneUndo {
    Disciplina disciplinaStearsa;
    Repo &repo;
public:
    UndoSterge(Repo& repo, const Disciplina& d): repo { repo }, disciplinaStearsa { d }{}
    void doUndo() override;
};

class UndoModifica: public ActiuneUndo {
    Disciplina disciplinaNoua;
    Disciplina disciplinaVeche;
    Repo &repo;
public:
    UndoModifica(Repo& repo, const Disciplina& disNoua, const Disciplina& disVeche): repo { repo }, disciplinaNoua { disNoua }, disciplinaVeche { disVeche }{}
    void doUndo() override;
};