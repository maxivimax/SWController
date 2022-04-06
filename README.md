# SWController
 
![IMG](./ReadMe.png "SWC")

[RU](https://github.com/maxivimax/SWController/blob/main/README.md)/[EN](https://github.com/maxivimax/SWController/blob/main/READMEen.md)

> A template for creating new repositories in the @orbitdb organization

This repository is meant to serve as a general template for how to set up new repositories in the @orbitdb organization. In general, setting up a new repository should take only a few minutes; use this repository as a way of finding example files, and use the following checklist to ensure that you've set up the repository correctly.

## Install

These instructions are basic; you can use any method to do this work. The important part is making sure that you follow the checklist below before publishing the repository.

```sh
# Let's make a new folder
mkdir new-repo && cd new-repo
# Start a Git instance and copy over template files.
git init
cp ../repo-template/* .
# Overwrite this README
mv README.md setup-checklist.md
mv example-README.md README.md
# Go over and check off the checklist, and finally
rm setup-checklist
```

## Checklist

Go through this checklist after creating your repository. It should only take a couple of minutes; if there is a way to make this more efficient, open an issue and let's talk about it here! \m/

### README
- [ ] Copy `example-README.md` from this repository to your directory.
- [ ] Rename all instances of `<Replace Title>` in README to match the new repo title
- [ ] Manually go through and edit the rest of the README.

### Other Files
- [ ] Copy `CODE_OF_CONDUCT.md` verbatim.
- [ ] Copy `CONTRIBUTING.md` and ensure that you've added any repository-specific instructions. (Replace `<Replace Title>` again).
- [ ] Should you have a `CHANGELOG.md`? Document your release process, if you plan on having one, in the `CONTRIBUTING.md` file.

### Dotfiles
- [ ] Do you need a `.gitignore` file?
