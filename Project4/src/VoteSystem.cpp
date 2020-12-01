#include "VoteSystem.hpp"

bool compare_by_word(Candidate candidate1,Candidate candidate2)
{
    return candidate1.get_votee()->get_name() < candidate2.get_votee()->get_name();
}
bool compare_by_number(Candidate candidate1,Candidate candidate2)
{
    return candidate1.get_number_of_votes() > candidate2.get_number_of_votes();
}

void VoteSystem::new_vote(Player *voter,Player *votee)
{
	Vote *existing_vote = get_vote(voter);
	if(existing_vote == nullptr) votes.push_back(new Vote(voter,votee));
	else existing_vote->change_votee(votee);
}

Vote* VoteSystem::get_vote(Player *voter)
{
	for(int i = 0;i < votes.size();i++)
	{
		if(voter == votes[i]->get_voter()) return votes[i];
	}
	return nullptr;
}

Player* VoteSystem::get_elected_player()
{
	create_candidate();
	if(candidates.size() > 0)
	{
		sort(candidates.begin(),candidates.end(),compare_by_number);
		eliminate_fewer_votes();
		sort(candidates.begin(),candidates.end(),compare_by_word);
		return candidates[0].get_votee();
	}
	else return nullptr;
}

void VoteSystem::create_candidate()
{
	for(int i = 0;i < votes.size();i++)
	{
		if(!candidate_exists(votes[i]->get_votee()))
			candidates.push_back(Candidate(votes[i]->get_votee()));
	}
}

bool VoteSystem::candidate_exists(Player *player)
{
	for(int i = 0;i < candidates.size();i++)
	{
		if((Player*)candidates[i].get_votee() == player)
		{
			candidates[i].increase_vote();
			return true;
		}
	}
	return false;
}

void VoteSystem::eliminate_fewer_votes()
{
	int highest_number_of_votes = candidates[0].get_number_of_votes();
	for(int i = 1;i < candidates.size();i++)
	{
		if(highest_number_of_votes > candidates[i].get_number_of_votes())
			candidates.erase(candidates.begin() + i);
	}
}

void VoteSystem::clear()
{
	for(int i = 0;i < votes.size();i++)
	{
		delete votes[i];
		votes.erase(votes.begin() + i);
	}

	for(int j =0;j < candidates.size();j++)
	{
		candidates.erase(candidates.begin() + j);
	}
}








